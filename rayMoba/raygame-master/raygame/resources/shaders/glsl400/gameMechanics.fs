#version 400

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

// NOTE: Render size values must be passed from code
const float renderWidth = 800;
const float renderHeight = 450;
vec2 screenResolution = vec2(renderWidth,renderHeight);

//vec4 getPixelRelative(int x, int y)
//{
//    return texture(texture0, fragTexCoord + vec2(x/renderWidth,y/renderHeight));
//}
//
//vec4 getPixelAt(int x, int y)
//{
//    return texture(texture0, vec2(x/renderWidth,y/renderHeight));
//}
//
//float inverseDistance(vec2 a, vec2 b)
//{
//    float dist =distance(a*screenResolution,b*screenResolution);
//    if(dist != 0.0f)
//    {
//        return 1/dist;
//    } else {
//        return 1;
//    }
//}

void main()
{
    float brightness = 0.5f;
    int x = 1;
    //while(getPixelAt(x,1).z > 0).0f{
    //    brightness += inverseDistance(vec2(getPixelAt(x,1).x,getPixelAt(x,1).y),fragTexCoord);
    //}
    finalColor = vec4(brightness,brightness,brightness, 1.0);
}