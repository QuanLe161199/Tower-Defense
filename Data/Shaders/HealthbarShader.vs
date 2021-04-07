attribute 	vec3 	a_posL;
attribute 	vec2 	a_uv;

uniform 	mat4 	u_matMVP;

uniform		float	u_trend;
uniform		float	u_numTrends;
uniform		float	u_numFrames;
uniform		float	u_currentFrame;

varying 	vec2 	v_uv;

void main()
{
	vec4 posL = vec4(a_posL, 1.0);
	gl_Position = u_matMVP * posL;
	v_uv = vec2(a_uv.x * 1.0 / u_numFrames + u_currentFrame / u_numFrames, a_uv.y * 1.0 / u_numTrends + u_trend / u_numTrends);
}
   