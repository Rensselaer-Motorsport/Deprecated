//Inspiration and basis from
// http://bl.ocks.org/tomerd/1499279
//Developed as part of the Adaptive Automotive Sensor Logger Project
//Featuring a simplified API and dashboard functionality
//woooooooowowowooooooo



//*****************************************************************
//***                   Update Gauges Realtime!                 ***
//*****************************************************************

function updateGauge(gauge, value) {
	gauges[gauge].redraw(value);
}
			
//'creates the gauge objects', and sets a javascript interval to trigger updating values
function initialize() {
	createGauges();
}
			
//*****************************************************************
			
//*****************************************************************
//***              Gauge Visualization Helpers                  ***
//*****************************************************************	
			
function createGauge(name, label,size, min, max, yellowlevel, redlevel)
{
	var config = 
	{
		size: size,
		label: label,
		min: undefined != min ? min : 0,
		max: undefined != max ? max : 100,
		yellowlevel: undefined != yellowlevel ? yellowlevel : (min + (max - min)*0.75),
		redlevel: undefined != redlevel ? redlevel : (min + (max - min)*0.90),
		minorTicks: 5
	}	

	config.yellowZones = [{ from: config.yellowlevel, to: config.redlevel }];
	config.redZones = [{ from: config.redlevel, to: config.max }];
				
	gauges[name] = new Gauge(name + "_gauge", config);
	gauges[name].render();
}

//*****************************************************************











//*****************************************************************
//***                Gauge Visualization Stuff                  ***
//*****************************************************************	
function Gauge(placeholderName, configuration)
{
	this.placeholderName = placeholderName;
	
	var self = this; // A copy for internal d3 functions, since d3 doesn't like it when you touch it sometimes
	
	this.configure = function(configuration)
	{
		this.config = configuration;
		
		this.config.size = this.config.size * 0.9;
		
		this.config.majorTicks = configuration.majorTicks || 5;
		this.config.minorTicks = configuration.minorTicks || 2;		
		
		this.config.raduis = this.config.size * 0.97 / 2;
		this.config.cx = this.config.size / 2;
		this.config.cy = this.config.size / 2;
		
		this.config.min = undefined != configuration.min ? configuration.min : 0; 
		this.config.max = undefined != configuration.max ? configuration.max : 100; 
		this.config.range = this.config.max - this.config.min;
	
		this.config.yellowColor = configuration.yellowColor || "#FF8800";
		this.config.redColor 	= configuration.redColor || "#EE3913";
		
		//Set this based on expected update speed - if consistent, use the period of the update 200ms gives a nice smooth update for most things. It will jump if a new even occurs before the transition is finished.
		this.config.transitionDuration = configuration.transitionDuration || 200;
	}

	this.render = function()
	{
		this.body = d3.select("#" + this.placeholderName)
			.append("svg:svg")
			.attr("class", "gauge")
			.attr("width", this.config.size)
			.attr("height", this.config.size);
		
		this.body.append("svg:circle")
			.attr("cx", this.config.cx)
			.attr("cy", this.config.cy)
			.attr("r", this.config.raduis)
			.style("fill", "#EEE")
			.style("stroke", "#222")
			.style("stroke-width", "3px");
					
		this.body.append("svg:circle")
			.attr("cx", this.config.cx)
			.attr("cy", this.config.cy)
			.attr("r", 0.9 * this.config.raduis)
			.style("fill", "#FFF")
		
		for (var index in this.config.yellowZones)
		{
			this.drawBand(this.config.yellowZones[index].from, this.config.yellowZones[index].to, self.config.yellowColor);
		}
		
		for (var index in this.config.redZones)
		{
			this.drawBand(this.config.redZones[index].from, this.config.redZones[index].to, self.config.redColor);
		}
		
		if (undefined != this.config.label)
		{
			var fontSize = Math.round(this.config.size / 9);
			this.body.append("svg:text")   //Styling for the gauge 'title' goes here
				.attr("x", this.config.cx)
				.attr("y", this.config.cy / 2 + fontSize / 2)
				.attr("dy", fontSize / 2.1)
				.attr("text-anchor", "middle")
				.text(this.config.label)
				.style("font-size", fontSize + "px")
				.style("font-family", "Squada One")
		}
		
		var fontSize = Math.round(this.config.size / 16);
		var majorDelta = this.config.range / (this.config.majorTicks - 1);
		for (var major = this.config.min; major <= this.config.max; major += majorDelta)
		{
			var minorDelta = majorDelta / this.config.minorTicks;
			for (var minor = major + minorDelta; minor < Math.min(major + majorDelta, this.config.max); minor += minorDelta)
			{
				var point1 = this.valueToPoint(minor, 0.75);
				var point2 = this.valueToPoint(minor, 0.85);
				
				this.body.append("svg:line")
					.attr("x1", point1.x)
					.attr("y1", point1.y)
					.attr("x2", point2.x)
					.attr("y2", point2.y)
					.style("stroke", "#666")
					.style("stroke-width", "1px");
			}
			
			var point1 = this.valueToPoint(major, 0.7);
			var point2 = this.valueToPoint(major, 0.85);	
			
			this.body.append("svg:line")
				.attr("x1", point1.x)
				.attr("y1", point1.y)
				.attr("x2", point2.x)
				.attr("y2", point2.y)
				.style("stroke", "#333")
				.style("stroke-width", "2px");
		
			if (major == this.config.min || major == this.config.max)
			{
				var point = this.valueToPoint(major, 0.63);
				
				//Styles for the gauge limits go here
				this.body.append("svg:text")
				 	.attr("x", point.x)
				 	.attr("y", point.y)
				 	.attr("dy", fontSize / 3)
				 	.attr("text-anchor", major == this.config.min ? "start" : "end")
					.style("font-family", "Squada One")
				 	.text(major)
				 	.style("font-size", fontSize + "px")

			}
		}
		
		var pointerContainer = this.body.append("svg:g").attr("class", "pointerContainer");
		
		var midValue = (this.config.min + this.config.max) / 2;
		
		var pointerPath = this.buildPointerPath(midValue);
		
		var pointerLine = d3.svg.line()
			.x(function(d) { return d.x })
			.y(function(d) { return d.y })
			.interpolate("basis");
		
		pointerContainer.selectAll("path")
			.data([pointerPath])
			.enter()
			.append("svg:path")
			.attr("d", pointerLine)
			.style("fill", "#DD3912")
			.style("stroke", "#CC3310")
			.style("fill-opacity", 0.7)
					
		pointerContainer.append("svg:circle")
			.attr("cx", this.config.cx)
			.attr("cy", this.config.cy)
			.attr("r", 0.07 * this.config.raduis)
			.style("fill", "#000")
			.style("opacity", 1);
		
		var fontSize = Math.round(this.config.size / 10);
		pointerContainer.selectAll("text")
			.data([midValue])
			.enter()
			//Styling for the gauge value goes here
			.append("svg:text")
			.attr("x", this.config.cx)
			.attr("y", this.config.size - this.config.cy / 4 - fontSize)
			.attr("dy", fontSize / 2.1)
			.attr("text-anchor", "middle")
			.style("font-family", "Squada One")
			.style("font-size", fontSize + "px")
		
		this.redraw(this.config.min, 0);
	}
	
	this.buildPointerPath = function(value)
	{
		var delta = this.config.range / 13;
		
		var head = valueToPoint(value, 0.85);
		var head1 = valueToPoint(value - delta, 0.12);
		var head2 = valueToPoint(value + delta, 0.12);
		
		var tailValue = value - (this.config.range * (1/(270/360)) / 2);
		var tail = valueToPoint(tailValue, 0.28);
		var tail1 = valueToPoint(tailValue - delta, 0.12);
		var tail2 = valueToPoint(tailValue + delta, 0.12);
		
		return [head, head1, tail2, tail, tail1, head2, head];
		
		function valueToPoint(value, factor)
		{
			var point = self.valueToPoint(value, factor);
			point.x -= self.config.cx;
			point.y -= self.config.cy;
			return point;
		}
	}
	
	this.drawBand = function(start, end, color)
	{
		if (0 >= end - start) return;
		
		this.body.append("svg:path")
					.style("fill", color)
					.attr("d", d3.svg.arc()
						.startAngle(this.valueToRadians(start))
						.endAngle(this.valueToRadians(end))
						.innerRadius(0.65 * this.config.raduis)
						.outerRadius(0.85 * this.config.raduis))
					.attr("transform", function() { return "translate(" + self.config.cx + ", " + self.config.cy + ") rotate(270)" });
	}
	
	this.redraw = function(value, transitionDuration)
	{
		var pointerContainer = this.body.select(".pointerContainer");
		
		pointerContainer.selectAll("text").text(Math.round(value));
		
		var pointer = pointerContainer.selectAll("path");
		pointer.transition()
					.duration(undefined != transitionDuration ? transitionDuration : this.config.transitionDuration)

					.attrTween("transform", function()
					{
						var pointerValue = value;
						if (value > self.config.max) pointerValue = self.config.max + 0.02*self.config.range;
						else if (value < self.config.min) pointerValue = self.config.min - 0.02*self.config.range;
						var targetRotation = (self.valueToDegrees(pointerValue) - 90);
						var currentRotation = self._currentRotation || targetRotation;
						self._currentRotation = targetRotation;
						
						return function(step) 
						{
							var rotation = currentRotation + (targetRotation-currentRotation)*step;
							return "translate(" + self.config.cx + ", " + self.config.cy + ") rotate(" + rotation + ")"; 
						}
					});
	}
	
	
	//These seem to work...
	this.valueToDegrees = function(value)
	{
		return value * 270 / this.config.range - (this.config.min * 270 / this.config.range + 45);
	}
	
	this.valueToRadians = function(value)
	{
		return this.valueToDegrees(value) / 180 * Math.PI ;
	}
	
	this.valueToPoint = function(value, factor)
	{
		return { 	x: this.config.cx - this.config.raduis * factor * Math.cos(this.valueToRadians(value)),
					y: this.config.cy - this.config.raduis * factor * Math.sin(this.valueToRadians(value)) 		};
	}
	
	// initialization
	this.configure(configuration);	
	
	//Load up the fonts here. Cache locally for non-internet-connected use...
	WebFontConfig = {
		google: { families: [ 'Squada+One::latin' ] }
	};
	(function() {
		var wf = document.createElement('script');
		wf.src = ('https:' == document.location.protocol ? 'https' : 'http') +
		'://ajax.googleapis.com/ajax/libs/webfont/1/webfont.js';
		wf.type = 'text/javascript';
		wf.async = 'true';
		var s = document.getElementsByTagName('script')[0];
		s.parentNode.insertBefore(wf, s);
	})();
  }
//*****************************************************************
