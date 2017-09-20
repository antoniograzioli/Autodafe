#include "Autodafe.hpp"


struct Multiple28 : Module{
	enum ParamIds {
		
		NUM_PARAMS
	};
	enum InputIds {
		INPUT1,
		INPUT2,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT11,
		OUT12,
		OUT13,
		OUT14,
		OUT15,
		OUT16,
		OUT17,
		OUT18,
		OUT21,
		OUT22,
		OUT23,
		OUT24,
		OUT25,
		OUT26,
		OUT27,
		OUT28,
		NUM_OUTPUTS
	};

	

	Multiple28();
	void step();
};


Multiple28::Multiple28() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);
}


void Multiple28::step() {
	
	float IN1 = getf(inputs[INPUT1]);
	float IN2 = getf(inputs[INPUT2]);

	// Set outputs
	//first column
	if (outputs[OUT11]) {
		*outputs[OUT11] = IN1;
	}
	
	if (outputs[OUT12]) {
		*outputs[OUT12] = IN1;
	}

	if (outputs[OUT13]) {
		*outputs[OUT13] = IN1;
	}

	if (outputs[OUT14]) {
		*outputs[OUT14] = IN1;
	}

	if (outputs[OUT15]) {
		*outputs[OUT15] = IN1;
	}

	if (outputs[OUT16]) {
		*outputs[OUT16] = IN1;
	}

	if (outputs[OUT17]) {
		*outputs[OUT17] = IN1;
	}

	if (outputs[OUT18]) {
		*outputs[OUT18] = IN1;
	}


	//SECOND COLUMN
	if (outputs[OUT21]) {
		*outputs[OUT21] = IN2;
	}

	if (outputs[OUT22]) {
		*outputs[OUT22] = IN2;
	}

	if (outputs[OUT23]) {
		*outputs[OUT23] = IN2;
	}

	if (outputs[OUT24]) {
		*outputs[OUT24] = IN2;
	}

	if (outputs[OUT25]) {
		*outputs[OUT25] = IN2;
	}

	if (outputs[OUT26]) {
		*outputs[OUT26] = IN2;
	}

	if (outputs[OUT27]) {
		*outputs[OUT27] = IN2;
	}

	if (outputs[OUT28]) {
		*outputs[OUT28] = IN2;
	}

	



	
}


Multiple28Widget::Multiple28Widget() {
	Multiple28 *module = new Multiple28();
	setModule(module);
	box.size = Vec(15*6, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load("plugins/Autodafe/res/Multiple28.svg"));
		addChild(panel);
	}

	addChild(createScrew<ScrewBlack>(Vec(15, 0)));
	addChild(createScrew<ScrewBlack>(Vec(15, 365)));
	addChild(createScrew<ScrewBlack>(Vec(60, 0)));
	addChild(createScrew<ScrewBlack>(Vec(60, 365)));

	

	addInput(createInput<PJ3410Port>(Vec(10, 20), module, Multiple28::INPUT1));
	addInput(createInput<PJ3410Port>(Vec(50, 20), module, Multiple28::INPUT2));
	
	addOutput(createOutput<PJ3410Port>(Vec(10, 60), module, Multiple28::OUT11));
	addOutput(createOutput<PJ3410Port>(Vec(10, 95), module, Multiple28::OUT12));
	addOutput(createOutput<PJ3410Port>(Vec(10, 130), module, Multiple28::OUT13));
	addOutput(createOutput<PJ3410Port>(Vec(10, 165), module, Multiple28::OUT14));
	addOutput(createOutput<PJ3410Port>(Vec(10, 200), module, Multiple28::OUT15));
	addOutput(createOutput<PJ3410Port>(Vec(10, 235), module, Multiple28::OUT16));
	addOutput(createOutput<PJ3410Port>(Vec(10, 270), module, Multiple28::OUT17));
	addOutput(createOutput<PJ3410Port>(Vec(10, 305), module, Multiple28::OUT18));

	addOutput(createOutput<PJ3410Port>(Vec(50, 60), module, Multiple28::OUT21));
	addOutput(createOutput<PJ3410Port>(Vec(50, 95), module, Multiple28::OUT22));
	addOutput(createOutput<PJ3410Port>(Vec(50, 130), module, Multiple28::OUT23));
	addOutput(createOutput<PJ3410Port>(Vec(50, 165), module, Multiple28::OUT24));
	addOutput(createOutput<PJ3410Port>(Vec(50, 200), module, Multiple28::OUT25));
	addOutput(createOutput<PJ3410Port>(Vec(50, 235), module, Multiple28::OUT26));
	addOutput(createOutput<PJ3410Port>(Vec(50, 270), module, Multiple28::OUT27));
	addOutput(createOutput<PJ3410Port>(Vec(50, 305), module, Multiple28::OUT28));

	
}


