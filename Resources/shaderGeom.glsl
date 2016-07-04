#version 120

#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4: enable

void main() {
    
    float light_radius = 0.3;
    
    // Do this once and we inherit for all new verts
    // Grab from fixed function style color in vert shader
    gl_FrontColor = gl_FrontColorIn[0];
    
    // Link below explains how built in outputs of vert shader
    // get turned into ins like gl_FrontColorIn / gl_PositionIn
    // in geo shader
    // This doesn't work w/o the gpu_shader4 extension
    // https://www.opengl.org/registry/specs/EXT/geometry_shader4.txt
    
    // Billboarding idea from:
    // http://www.geeks3d.com/20140815/particle-billboarding-with-the-geometry-shader-glsl/
    
    vec4 P = gl_PositionIn[0];
    
    // a: left-bottom
    vec2 va = P.xy + vec2(-0.5, -0.5) * light_radius;
    gl_Position = gl_ProjectionMatrix * vec4(va, P.zw);
    gl_TexCoord[0].xy = vec2(0.0, 64.0);
    EmitVertex();
    
    // b: left-top
    vec2 vb = P.xy + vec2(-0.5, 0.5) * light_radius;
    gl_Position = gl_ProjectionMatrix * vec4(vb, P.zw);
    gl_TexCoord[0].xy = vec2(0.0, 0.0);
    EmitVertex();
    
    // d: right-bottom
    vec2 vd = P.xy + vec2(0.5, -0.5) * light_radius;
    gl_Position = gl_ProjectionMatrix * vec4(vd, P.zw);
    gl_TexCoord[0].xy = vec2(64.0, 64.0);
    EmitVertex();
    
    // c: right-top
    vec2 vc = P.xy + vec2(0.5, 0.5) * light_radius;
    gl_Position = gl_ProjectionMatrix * vec4(vc, P.zw);
    gl_TexCoord[0].xy = vec2(64.0, 0.0);
    EmitVertex();
    
    EndPrimitive();
    
}