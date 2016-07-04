#version 120

#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4: enable

uniform sampler2DRect lightDot;

void main() {
    
    vec4 opacity = texture2DRect(lightDot, gl_TexCoord[0].xy);
    gl_FragColor = vec4(gl_Color.xyz, opacity.x);
    
}
