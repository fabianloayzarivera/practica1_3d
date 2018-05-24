attribute vec3 vpos;
attribute vec4 vcolor;
varying vec4 fcolor;

void main() {
	gl_Position = vec4(vpos, 1);
	fcolor = vcolor;
}