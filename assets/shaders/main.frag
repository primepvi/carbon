#version 330 core

in vec4 v_color;
in vec2 v_texCoords;
flat in int v_texIndex;

out vec4 frag_color;

uniform sampler2D u_textures[16];

void main()
{
    vec4 texColor;

    switch (v_texIndex)
    {
        case 0:
            texColor = texture(u_textures[0], v_texCoords);
            break;
        case 1:
            texColor = texture(u_textures[1], v_texCoords);
            break;
        case 2:
            texColor = texture(u_textures[2], v_texCoords);
            break;
        case 3:
            texColor = texture(u_textures[3], v_texCoords);
            break;
        case 4:
            texColor = texture(u_textures[4], v_texCoords);
            break;
        case 5:
            texColor = texture(u_textures[5], v_texCoords);
            break;
        case 6:
            texColor = texture(u_textures[6], v_texCoords);
            break;
        case 7:
            texColor = texture(u_textures[7], v_texCoords);
            break;
        case 8:
            texColor = texture(u_textures[8], v_texCoords);
            break;
        case 9:
            texColor = texture(u_textures[9], v_texCoords);
            break;
        case 10:
            texColor = texture(u_textures[10], v_texCoords);
            break;
        case 11:
            texColor = texture(u_textures[11], v_texCoords);
            break;
        case 12:
            texColor = texture(u_textures[12], v_texCoords);
            break;
        case 13:
            texColor = texture(u_textures[13], v_texCoords);
            break;
        case 14:
            texColor = texture(u_textures[14], v_texCoords);
            break;
        case 15:
            texColor = texture(u_textures[15], v_texCoords);
            break;
        default:
            texColor = vec4(1.0);
            break;
    }

    frag_color = texColor * v_color;
}
