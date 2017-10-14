#include "Autodafe.hpp"
#include <math.h>




Plugin *plugin;

void init(rack::Plugin *p) {
	plugin = p;
	plugin->slug = "Autodafe";
	plugin->name = "Autodafe";
	plugin->homepageUrl = "https://www.autodafe.net";
		createModel<LFOWidget>(plugin, "LFO", "LFO");
		createModel<ClockDividerWidget>(plugin, "Clock Divider", "Clock Divider");
		createModel<Multiple18Widget>(plugin, "Multiple 1x8", "Multiple 1x8");
		createModel<Multiple28Widget>(plugin, "Multiple 2x8", "Multiple 2x8");
		createModel<SEQ8Widget>(plugin, "8-Steps Sequencer", "8-Steps Sequencer");
		createModel<SEQ16Widget>(plugin, "16-Steps Sequencer", "16-Steps Sequencer");
		createModel<TriggerSeqWidget>(plugin, "8x16 Trigger Sequencer", "8x16 Trigger Sequencer");
		createModel<FixedFilterWidget>(plugin, "Fixed Filter Bank", "Fixed Filter Bank");
		createModel<MultiModeFilterWidget>(plugin, "MultiMode Filter", "MultiMode Filter ");
		createModel<FormantFilterWidget>(plugin, "Formant Filter", "Formant Filter");
		createModel<FoldBackWidget>(plugin, "Foldback Distortion", "Foldback Distortion");
		createModel<BitCrusherWidget>(plugin, "BitCrusher", "BitCrusher");
		createModel<PhaserFxWidget>(plugin, "Phaser", "Phaser");
		
		
		
		
		

		
		//printf("%p %p\n", plugin, &plugin);
		
		

	}


