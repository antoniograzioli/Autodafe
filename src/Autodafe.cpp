#include "Autodafe.hpp"
#include <math.h>
#include "dsp.hpp"



struct AutodafePlugin : Plugin {
	AutodafePlugin() {
		slug = "Autodafe";
		name = "Autodafe";
		
		createModel<LFOWidget>(this, "LFO", "LFO");
		createModel<ClockDividerWidget>(this, "Clock Divider", "Clock Divider");
		createModel<Multiple18Widget>(this, "Multiple 1x8", "Multiple 1x8");
		createModel<Multiple28Widget>(this, "Multiple 2x8", "Multiple 2x8");
		createModel<SEQ8Widget>(this, "8-Steps Sequencer", "8-Steps Sequencer");
		createModel<SEQ16Widget>(this, "16-Steps Sequencer", "16-Steps Sequencer");
		createModel<TriggerSeqWidget>(this, "8x16 Trigger Sequencer", "8x16 Trigger Sequencer");
		createModel<FixedFilterWidget>(this, "Fixed Filter Bank", "Fixed Filter Bank");
		createModel<FoldBackWidget>(this, "Foldback Distortion", "Foldback Distortion");
		createModel<BitCrusherWidget>(this, "BitCrusher", "BitCrusher");
		createModel<PhaserFxWidget>(this, "Phaser", "Phaser");
		

		
		
		

	}
};


Plugin *init() {
	return new AutodafePlugin();
}
