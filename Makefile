AUV: AUV.cpp texture.h define.h
	g++ AUV.cpp -o app -lglut -lGL -lGLU -lm -lX11 -g
clear: 
	rm app
