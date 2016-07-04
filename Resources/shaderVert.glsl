#version 120

#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4: enable

uniform sampler2DRect lightPixelBuffer;

void main() {
    
    // Just apply model view, not model view proj
    // We'll apply projection in the geom shader
    gl_Position = gl_ModelViewMatrix * gl_Vertex;
    
    // Sample the bound texture of the gate pixel array
    vec4 color = texture2DRect(lightPixelBuffer, gl_MultiTexCoord0.xy);
    
    // Put it into the fixed function gl_FrontColor for
    // reading in the geo / frag shader
    gl_FrontColor = vec4( color.xyz, 1.0 );
    
}