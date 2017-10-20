//**************************************************************************************
//Clock Divider Module for VCV Rack by Autodafe http://www.autodafe.net
//
//  Based on code created by Created by Nigel Redmon 
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//  http://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
//**************************************************************************************

#include "Autodafe.hpp"
#include <stdlib.h>





struct MultiModeFilter : Module{
	enum ParamIds {
		FREQ_PARAM,
		Q_PARAM,
		RES_PARAM,
		FREQ_CV_PARAM,
		FREQ_CV_PARAM2,
		DRIVE_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		FREQ_INPUT,
		FREQ_INPUT2,
		RES_INPUT,
		DRIVE_INPUT,
		INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUTLPF,
		OUTHPF,
		OUTBPF,
		OUTNPF,
		NUM_OUTPUTS
	};


	MultiModeFilter();
VAStateVariableFilter *lpFilter = new VAStateVariableFilter() ;	// create a lpFilter;
VAStateVariableFilter *hpFilter = new VAStateVariableFilter() ;	// create a lpFilter;
VAStateVariableFilter *bpFilter = new VAStateVariableFilter() ;	// create a lpFilter;
VAStateVariableFilter *npFilter = new VAStateVariableFilter() ;	// create a lpFilter;


	void step();
};













MultiModeFilter::MultiModeFilter() {
	params.resize(NUM_PARAMS);
	inputs.resize(NUM_INPUTS);
	outputs.resize(NUM_OUTPUTS);
}

float outLP;
float outHP;
float outBP;
float outNP;



//VAStateVariableFilter *peakFilter = new VAStateVariableFilter();

float minfreq = 15.0;
float maxfreq = 12000;



void MultiModeFilter::step() {
	
#ifdef v_dev
	float gSampleRate = engineGetSampleRate();
#endif	

	float input = inputs[INPUT].value / 5.0;
	float drive = params[DRIVE_PARAM].value + inputs[DRIVE_INPUT].value / 10.0;
	float gain = powf(100.0, drive);
	input *= gain;
	// Add -60dB noise to bootstrap self-oscillation
	input += 1.0e-6 * (2.0*randomf() - 1.0)*1000;

	// Set resonance
	float res = clampf(params[RES_PARAM].value + clampf(inputs[RES_INPUT].value, 0,1), 0,1);
	//res = 5.5 * clampf(res, 0.0, 1.0);
	

	float cutoffcv =  400*params[FREQ_CV_PARAM].value * inputs[FREQ_INPUT].value+ 400*inputs[FREQ_INPUT2].value *params[FREQ_CV_PARAM2].value ;
	
	float cutoff = params[FREQ_PARAM].value + cutoffcv;

	cutoff = clampf(cutoff, minfreq, maxfreq);
	

 

	lpFilter->setFilterType(0);
	hpFilter->setFilterType(2);
	bpFilter->setFilterType(1);
	npFilter->setFilterType(5);

	
	lpFilter->setCutoffFreq(cutoff);
	hpFilter->setCutoffFreq(cutoff); 
	bpFilter->setCutoffFreq(cutoff);
	npFilter->setCutoffFreq(cutoff);


	lpFilter->setResonance(res);
	hpFilter->setResonance(res);
	bpFilter->setResonance(res);
	npFilter->setResonance(res);





	lpFilter->setSampleRate(gSampleRate);
	hpFilter->setSampleRate(gSampleRate);
	bpFilter->setSampleRate(gSampleRate);
	npFilter->setSampleRate(gSampleRate);





	outLP = lpFilter->processAudioSample(input,1);
	outHP = hpFilter->processAudioSample(input,1);
	outBP = bpFilter->processAudioSample(input,1);
	outNP = npFilter->processAudioSample(input,1);




	outputs[OUTLPF].value=outLP*5;
	outputs[OUTHPF].value= outHP*5;
	outputs[OUTBPF].value= outBP*5;
	outputs[OUTNPF].value= outNP*5;

	



}

MultiModeFilterWidget::MultiModeFilterWidget() {
	MultiModeFilter *module = new MultiModeFilter();
	setModule(module);
	box.size = Vec(15 * 13, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin,"res/MultiModeFilter.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(15, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 0)));
	addChild(createScrew<ScrewSilver>(Vec(15, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 30, 365)));

	addParam(createParam<Davies1900hLargeBlackKnob>(Vec(68, 61), module, MultiModeFilter::FREQ_PARAM, minfreq, maxfreq, maxfreq));
	
	addParam(createParam<Davies1900hBlackKnob>(Vec(111, 143), module, MultiModeFilter::RES_PARAM, 0.0, 0.99, 0.0));
	addParam(createParam<Davies1900hBlackKnob>(Vec(43, 143), module, MultiModeFilter::FREQ_CV_PARAM, -1.0, 1.0, 0.0));

	addParam(createParam<Davies1900hBlackKnob>(Vec(43, 208), module, MultiModeFilter::FREQ_CV_PARAM2, -1.0, 1.0, 0.0));


	addParam(createParam<Davies1900hBlackKnob>(Vec(111, 208), module, MultiModeFilter::DRIVE_PARAM, 0.0, 1.0, 0.0));





	addInput(createInput<PJ301MPort>(Vec(10, 276), module, MultiModeFilter::FREQ_INPUT));
	addInput(createInput<PJ301MPort>(Vec(121, 276), module, MultiModeFilter::FREQ_INPUT2));
	addInput(createInput<PJ301MPort>(Vec(48, 276), module, MultiModeFilter::RES_INPUT));
	addInput(createInput<PJ301MPort>(Vec(85, 276), module, MultiModeFilter::DRIVE_INPUT));

	addInput(createInput<PJ301MPort>(Vec(10, 320), module, MultiModeFilter::INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(48, 320), module, MultiModeFilter::OUTLPF));
	addOutput(createOutput<PJ301MPort>(Vec(85, 320), module, MultiModeFilter::OUTHPF));
	addOutput(createOutput<PJ301MPort>(Vec(122, 320), module, MultiModeFilter::OUTBPF));
	addOutput(createOutput<PJ301MPort>(Vec(159, 320), module, MultiModeFilter::OUTNPF));

}