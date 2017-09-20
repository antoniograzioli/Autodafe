#include "Autodafe.hpp"
#include <math.h>
#include "dsp.hpp"


struct AutodafePlugin : Plugin {
	AutodafePlugin() {
		slug = "Autodafe";
		name = "Autodafe";
		
		createModel<LFOWidget>(this, "LFO", "LFO");
		
		createModel<ClockDividerWidget>(this, "Clock Divider", "Clock Divider");
		createModel<Multiple28Widget>(this, "2x8 Multiple", "2x8 Multiple");

		createModel<VCBPFWidget>(this, "BandPass Filter", "BandPass Filter");
		
	}
};


Plugin *init() {
	return new AutodafePlugin();
}
