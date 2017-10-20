//**************************************************************************************
//8-Steps Sequencer Module for VCV Rack by Autodafe http://www.autodafe.net
//
//Based on code taken from the Fundamentals plugins by Andrew Belt http://www.vcvrack.com
//
//**************************************************************************************

#include "Autodafe.hpp"
#include "dsp/digital.hpp"



struct TriggerSeq : Module {
	enum ParamIds {
		CLOCK_PARAM,
		RUN_PARAM,
		RESET_PARAM,
		STEPS_PARAM,

		GATE_PARAM,
		NUM_PARAMS = GATE_PARAM+128
	};

	enum InputIds {
		CLOCK_INPUT,
		EXT_CLOCK_INPUT,
		RESET_INPUT, 
		STEPS_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		GATES_OUTPUT,
		NUM_OUTPUTS = GATES_OUTPUT + 8
	};

	bool running = true;
	SchmittTrigger clockTrigger; // for external clock
	SchmittTrigger runningTrigger;
	SchmittTrigger resetTrigger;
	float phase = 0.0;
	int index = 0;
	SchmittTrigger gateTriggers[8][16];
	bool gateState[8][16]={};



	float stepLights[8][16] ;

	// Lights
	float runningLight = 0.0;
	float resetLight = 0.0;
	float gatesLight[8];
	float rowLights[8][16] ;
	float gateLights[8][16];





	TriggerSeq();
	void step();










	json_t *toJson() {

		json_t *rootJtrigseq = json_object();

		json_t *gatesJtrigSeq = json_array();
		for (int z = 0; z < 8; z++) {
			
			for (int i = 0; i < 16; i++) {
				json_t *gateJtrigseq = json_integer((int)gateState[z][i]);
				json_array_append_new(gatesJtrigSeq, gateJtrigseq);
			}
		}
		json_object_set_new(rootJtrigseq, "gatesTrigSeq", gatesJtrigSeq);

		return rootJtrigseq;
	}

	void fromJson(json_t *rootJtrigseq) {


for (int z = 0; z < 8; z++) {
			
			for (int i = 0; i < 16; i++) {
				gateState[z][i] = false;
				
			}
		}






		
		json_t *gatesJtrigSeq = json_object_get(rootJtrigseq, "gatesTrigSeq");
		for (int z = 0; z < 8; z++) {
			
			for (int i = 0; i < 16; i++) {
			

				json_t *gateJtrigseq = json_array_get(gatesJtrigSeq, z*16+i);
				gateState[z][i] = !!json_integer_value(gateJtrigseq);

			}
		}
	}
#ifdef v_dev
	void reset() {
#else
	void initialize() {
#endif		
		for (int z = 0; z < 8; z++) {
			for (int i = 0; i < 16; i++) {
			
				gateState[z][i] = false;
				}
			}
		}

	void randomize() {
		for (int z = 0; z < 8; z++) {
		for (int i = 0; i < 16; i++) {
			
				gateState[z][i] = (randomf() > 0.5);
			}
		}
	}
};


TriggerSeq::TriggerSeq() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);
}




void TriggerSeq::step() {
	
#ifdef v_dev
	float gSampleRate = engineGetSampleRate();
#endif

	float gate[8] = { 0 };
	
	const float lightLambda = 0.05;
	
		// Run
		if (runningTrigger.process(params[RUN_PARAM].value)) {
			running = !running;
		}
		runningLight = running ? 1.0 : 0.0;

		bool nextStep = false;

		if (running) {
			if (inputs[EXT_CLOCK_INPUT].active) {
				// External clock
				if (clockTrigger.process(inputs[EXT_CLOCK_INPUT].value)) {
					phase = 0.0;
					nextStep = true;
				}
			}
			else {
				// Internal clock
				float clockTime = powf(2.0, params[CLOCK_PARAM].value+ inputs[CLOCK_INPUT].value);
				phase += clockTime / gSampleRate;
				if (phase >= 1.0) {
					phase -= 1.0;
					nextStep = true;
				}
			}
		}

		// Reset
		if (resetTrigger.process(params[RESET_PARAM].value + inputs[RESET_INPUT].value)) {
			phase = 0.0;
			index = 999;
			nextStep = true;
			resetLight = 1.0;
		}

		if (nextStep)	{

			// Advance step
			int numSteps = clampi(roundf(params[STEPS_PARAM].value + inputs[STEPS_INPUT].value), 1, 16);
			index += 1;
							if (index >= numSteps) {
								index = 0;
							}
			
							for (int z = 0; z < 8; z++) {
								stepLights[z][index] = 1.0;
							}
			}
			


		resetLight -= resetLight / lightLambda / gSampleRate;


		// Gate buttons

		for (int z = 0; z < 8; z++) {

		for (int i = 0; i < 16; i++) {

			if (gateTriggers[z][i].process(params[GATE_PARAM + z*16+i].value)) {
				gateState[z][i] = !gateState[z][i];

			}

			

			gate[z] = (gateState[z][index] >= 1.0) && !nextStep ? 10.0 : 0.0;
			outputs[GATES_OUTPUT + z].value= gate[z];
			stepLights[z][i] -= stepLights[z][i] / lightLambda / gSampleRate;
			gateLights[z][i] = (gateState[z][i] >= 1.0) ? 1.0 - stepLights[z][i] : stepLights[z][i];

			


		} 


		gatesLight[z] = (gateState[z][index] >= 1.0) ? 1.0 : 0.0;
	}
	
}



 
     
    
TriggerSeqWidget::TriggerSeqWidget() { 
	TriggerSeq *module = new TriggerSeq();
	setModule(module);    
	box.size = Vec(15*45, 380);
 
	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/TriggerSeq.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(5, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-20, 0)));
	addChild(createScrew<ScrewSilver>(Vec(5, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-20, 365)));

	addParam(createParam<Davies1900hSmallBlackKnob>(Vec(17, 56), module, TriggerSeq::CLOCK_PARAM, -2.0, 6.0, 2.0));
	addParam(createParam<LEDButton>(Vec(60, 61-1), module, TriggerSeq::RUN_PARAM, 0.0, 1.0, 0.0));
	addChild(createValueLight<SmallLight<GreenValueLight>>(Vec(60+5, 61+4), &module->runningLight));
	addParam(createParam<LEDButton>(Vec(98, 61-1), module, TriggerSeq::RESET_PARAM, 0.0, 1.0, 0.0));
	addChild(createValueLight<SmallLight<GreenValueLight>>(Vec(98+5, 61+4), &module->resetLight));
	addParam(createParam<Davies1900hSmallBlackSnapKnob>(Vec(132, 56), module, TriggerSeq::STEPS_PARAM, 1.0, 16.0, 16.0));
	
	

	static const float portX[16] = { 19, 57, 96, 134, 173, 211, 250, 288, 326, 364, 402, 440,478,516,554,592};

	//static const float portX[16] = { 20, 50, 80, 110, 140, 170, 200, 230, 260, 290, 320, 350,380,410,440,470};
	addInput(createInput<PJ301MPort>(Vec(portX[0]-1, 99-1), module, TriggerSeq::CLOCK_INPUT));
	addInput(createInput<PJ301MPort>(Vec(portX[1]-1, 99-1), module, TriggerSeq::EXT_CLOCK_INPUT));
	addInput(createInput<PJ301MPort>(Vec(portX[2]-1, 99-1), module, TriggerSeq::RESET_INPUT));
	addInput(createInput<PJ301MPort>(Vec(portX[3]-1, 99-1), module, TriggerSeq::STEPS_INPUT));
	
	

	for (int z = 0; z < 8; z++) 
	
	{

		//Gates Oututs
		addOutput(createOutput<PJ301MPort>(Vec(630, 140 + 25 * z - 5), module, TriggerSeq::GATES_OUTPUT+z));
		addChild(createValueLight<SmallLight<GreenValueLight>>(Vec(618, 143 + 25 * z), &module->gatesLight[z]));
		
	for (int i = 0; i < 16; i++) {
		//Lighst and Button Matrix
			addParam(createParam<LEDButton>(Vec(portX[i] + 2, 140  + 25  * z - 1), module, TriggerSeq::GATE_PARAM + z*16+i, 0.0, 1.0, 0.0));
        //addParam(createParam<AutodafeButton>(Vec(portX[i] + 2, 140  + 25  * z - 1), module, TriggerSeq::GATE_PARAM + z*16+i, 0.0, 1.0, 0.0));
        
			addChild(createValueLight<SmallLight<GreenValueLight>>(Vec(portX[i] + 7, 140 + 25 * z + 4), &module->gateLights[z][i]));
		}
	}

}
