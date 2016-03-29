//
//  DepthBlend.h
//  Philadelphia
//
//  Created by 麦 on 3/28/16.
//
//

#pragma once

#include "ofMain.h"
#include "ofxSwapBuffer.h"


class DepthBlend {
public:
	
	
	void allocate(int w, int h) {
		setSize(w, h);
		blendShader.load("depth-blend.vert", "depth-blend.frag");
		drawShader.load("depth-blend.vert", "ignore-alpha.frag");
	}
	
	void setSize(int w, int h) {
		width = w;
		height = h;
		pingPongMask.allocate(width, height, GL_RGB);
		bgTex.allocate(width, height, GL_RGB);
	}
	
	void clear() {
		bgTex.begin();
		ofClear(0);
		bgTex.end();
		
		pingPongMask.src->begin();

		ofClear(0);
		
		pingPongMask.src->end();
	}
	
	void blendDepth(ofTexture &depthTex) {
		
		pingPongMask.dst->begin();
		
		blendShader.begin();
		blendShader.setUniform2f("resolution", width, height);
		blendShader.setUniformTexture("maskTex", pingPongMask.src->getTexture(), 0);
		blendShader.setUniformTexture("depthTex", depthTex, 1);
		
		ofSetColor(255);
		ofDrawRectangle(0, 0, width, height);
		
		blendShader.end();
		pingPongMask.dst->end();
		
	}
	
	void bake() {
		cout << "swap" << endl;
		pingPongMask.swap();
	}
	
	void draw(ofTexture &rgbTex, bool isBake) {
		
		if (isBake) {
			bgTex.begin();
			cout << "bake" << endl;
		}
		
		drawShader.begin();
		drawShader.setUniform2f("resolution", width, height);
		drawShader.setUniformTexture("maskTex", pingPongMask.dst->getTexture(), 0);
		drawShader.setUniformTexture("bgTex", bgTex.getTexture(), 1);
		drawShader.setUniformTexture("fgTex", rgbTex, 2);
		
		ofSetColor(255);
		ofDrawRectangle(0, 0, width, height);
		
		
		drawShader.end();
		
		if (isBake) {
			bgTex.end();
			pingPongMask.swap();
			bgTex.draw(0, 0, width, height);
		}
	}
	
	int width, height;
	ofFbo bgTex;
	ofxSwapBuffer pingPongMask;
							
	ofShader blendShader, drawShader;
};