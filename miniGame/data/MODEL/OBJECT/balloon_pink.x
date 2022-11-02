xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 266;
 0.00000;133.00000;0.00000;,
 4.47947;131.84712;-10.81440;,
 0.00000;131.84712;-11.70542;,
 8.27698;131.84712;-8.27698;,
 10.81440;131.84712;-4.47947;,
 11.70542;131.84712;0.00000;,
 10.81440;131.84712;4.47947;,
 8.27698;131.84712;8.27698;,
 4.47947;131.84712;10.81440;,
 0.00000;131.84712;11.70542;,
 -4.47947;131.84712;10.81440;,
 -8.27698;131.84712;8.27698;,
 -10.81440;131.84712;4.47947;,
 -11.70542;131.84712;0.00000;,
 -10.81440;131.84712;-4.47947;,
 -8.27698;131.84712;-8.27698;,
 -4.47946;131.84712;-10.81440;,
 8.78680;128.43277;-21.21320;,
 0.00000;128.43277;-22.96101;,
 16.23589;128.43277;-16.23588;,
 21.21320;128.43277;-8.78680;,
 22.96101;128.43277;0.00000;,
 21.21320;128.43277;8.78680;,
 16.23588;128.43277;16.23588;,
 8.78680;128.43277;21.21320;,
 0.00000;128.43277;22.96101;,
 -8.78679;128.43277;21.21320;,
 -16.23588;128.43277;16.23589;,
 -21.21320;128.43277;8.78680;,
 -22.96101;128.43277;0.00000;,
 -21.21320;128.43277;-8.78680;,
 -16.23588;128.43277;-16.23589;,
 -8.78679;128.43277;-21.21321;,
 12.75645;122.88817;-30.79680;,
 0.00000;122.88817;-33.33422;,
 23.57085;122.88817;-23.57085;,
 30.79680;122.88817;-12.75645;,
 33.33422;122.88817;0.00000;,
 30.79680;122.88817;12.75645;,
 23.57085;122.88817;23.57085;,
 12.75645;122.88817;30.79680;,
 0.00001;122.88817;33.33422;,
 -12.75645;122.88817;30.79680;,
 -23.57084;122.88817;23.57086;,
 -30.79680;122.88817;12.75646;,
 -33.33422;122.88817;0.00000;,
 -30.79680;122.88817;-12.75646;,
 -23.57084;122.88817;-23.57086;,
 -12.75644;122.88817;-30.79681;,
 16.23588;116.42641;-39.19689;,
 0.00000;116.42641;-42.42641;,
 30.00000;116.42641;-30.00000;,
 39.19689;116.42641;-16.23588;,
 42.42641;116.42641;0.00000;,
 39.19689;116.42641;16.23589;,
 30.00000;116.42641;30.00000;,
 16.23589;116.42641;39.19689;,
 0.00001;116.42641;42.42641;,
 -16.23587;116.42641;39.19689;,
 -29.99999;116.42641;30.00001;,
 -39.19689;116.42641;16.23589;,
 -42.42641;116.42641;0.00000;,
 -39.19689;116.42641;-16.23589;,
 -29.99999;116.42641;-30.00001;,
 -16.23586;116.42641;-39.19690;,
 0.00000;116.42641;-42.42641;,
 16.23588;116.42641;-39.19689;,
 19.09138;107.33421;-46.09067;,
 0.00000;107.33421;-49.88818;,
 30.00000;116.42641;-30.00000;,
 35.27627;107.33421;-35.27627;,
 46.09067;107.33421;-19.09138;,
 35.27627;107.33421;-35.27627;,
 49.88818;107.33421;0.00000;,
 46.09066;107.33421;19.09138;,
 35.27627;107.33421;35.27627;,
 19.09138;107.33421;46.09066;,
 0.00001;107.33421;49.88818;,
 -19.09137;107.33421;46.09067;,
 -35.27626;107.33421;35.27628;,
 -46.09066;107.33421;19.09139;,
 -49.88818;107.33421;0.00000;,
 -46.09066;107.33421;-19.09139;,
 -35.27626;107.33421;-35.27628;,
 -29.99999;116.42641;-30.00001;,
 -16.23586;116.42641;-39.19690;,
 -19.09136;107.33421;-46.09068;,
 -35.27626;107.33421;-35.27628;,
 21.21320;97.96100;-51.21320;,
 0.00000;97.96100;-55.43277;,
 39.19689;97.96100;-39.19689;,
 51.21320;97.96100;-21.21320;,
 39.19689;97.96100;-39.19689;,
 55.43277;97.96100;0.00000;,
 51.21320;97.96100;21.21320;,
 39.19689;97.96100;39.19689;,
 21.21320;97.96100;51.21320;,
 0.00001;97.96100;55.43277;,
 -21.21319;97.96100;51.21321;,
 -39.19688;97.96100;39.19690;,
 -51.21320;97.96100;21.21321;,
 -55.43277;97.96100;0.00000;,
 -51.21320;97.96100;-21.21321;,
 -39.19688;97.96100;-39.19690;,
 -21.21318;97.96100;-51.21321;,
 -39.19688;97.96100;-39.19690;,
 22.51982;86.70542;-54.36765;,
 0.00000;86.70542;-58.84711;,
 41.61119;86.70542;-41.61119;,
 54.36765;86.70542;-22.51982;,
 41.61119;86.70542;-41.61119;,
 58.84711;86.70542;0.00000;,
 54.36765;86.70542;22.51982;,
 41.61119;86.70542;41.61119;,
 22.51982;86.70542;54.36765;,
 0.00001;86.70542;58.84711;,
 -22.51980;86.70542;54.36765;,
 -41.61118;86.70542;41.61121;,
 -54.36764;86.70542;22.51982;,
 -58.84711;86.70542;0.00000;,
 -54.36764;86.70542;-22.51983;,
 -41.61118;86.70542;-41.61121;,
 -22.51979;86.70542;-54.36766;,
 -41.61118;86.70542;-41.61121;,
 22.96101;75.00001;-55.43277;,
 0.00000;75.00001;-60.00000;,
 42.42641;75.00001;-42.42641;,
 55.43277;75.00001;-22.96100;,
 42.42641;75.00001;-42.42641;,
 60.00000;75.00001;0.00000;,
 55.43277;75.00001;22.96101;,
 42.42641;75.00001;42.42641;,
 22.96101;75.00001;55.43277;,
 0.00001;75.00001;60.00000;,
 -22.96099;75.00001;55.43278;,
 -42.42640;75.00001;42.42642;,
 -55.43277;75.00001;22.96101;,
 -60.00000;75.00001;0.00000;,
 -55.43277;75.00001;-22.96102;,
 -42.42639;75.00001;-42.42642;,
 -22.96098;75.00001;-55.43279;,
 -42.42639;75.00001;-42.42642;,
 22.51982;63.29459;-54.36765;,
 0.00000;63.29459;-58.84712;,
 41.61120;63.29459;-41.61120;,
 54.36765;63.29459;-22.51982;,
 41.61120;63.29459;-41.61120;,
 58.84712;63.29459;0.00000;,
 54.36765;63.29459;22.51982;,
 41.61120;63.29459;41.61120;,
 22.51982;63.29459;54.36765;,
 0.00001;63.29459;58.84712;,
 -22.51981;63.29459;54.36765;,
 -41.61118;63.29459;41.61121;,
 -54.36765;63.29459;22.51983;,
 -58.84712;63.29459;0.00000;,
 -54.36765;63.29459;-22.51983;,
 -41.61118;63.29459;-41.61121;,
 -22.51979;63.29459;-54.36766;,
 -41.61118;63.29459;-41.61121;,
 21.21320;52.03900;-51.21320;,
 0.00000;52.03900;-55.43278;,
 39.19689;52.03900;-39.19689;,
 51.21320;52.03900;-21.21320;,
 39.19689;52.03900;-39.19689;,
 55.43278;52.03900;0.00000;,
 51.21320;52.03900;21.21321;,
 39.19689;52.03900;39.19689;,
 21.21321;52.03900;51.21320;,
 0.00001;52.03900;55.43278;,
 -21.21319;52.03900;51.21321;,
 -39.19688;52.03900;39.19690;,
 -51.21320;52.03900;21.21321;,
 -55.43278;52.03900;0.00000;,
 -51.21320;52.03900;-21.21321;,
 -39.19688;52.03900;-39.19691;,
 -21.21318;52.03900;-51.21322;,
 -39.19688;52.03900;-39.19691;,
 19.09138;41.66579;-46.09067;,
 0.00000;41.66579;-49.88818;,
 35.27627;41.66579;-35.27627;,
 46.09067;41.66579;-19.09138;,
 35.27627;41.66579;-35.27627;,
 49.88818;41.66579;0.00000;,
 46.09066;41.66579;19.09138;,
 35.27627;41.66579;35.27627;,
 19.09138;41.66579;46.09066;,
 0.00001;41.66579;49.88818;,
 -19.09137;41.66579;46.09067;,
 -35.27626;41.66579;35.27628;,
 -46.09066;41.66579;19.09139;,
 -49.88818;41.66579;0.00000;,
 -46.09066;41.66579;-19.09139;,
 -35.27626;41.66579;-35.27628;,
 -19.09136;41.66579;-46.09068;,
 -35.27626;41.66579;-35.27628;,
 16.23588;32.57359;-39.19689;,
 0.00000;32.57359;-42.42641;,
 30.00000;32.57359;-30.00000;,
 39.19689;32.57359;-16.23588;,
 30.00000;32.57359;-30.00000;,
 42.42641;32.57359;0.00000;,
 39.19689;32.57359;16.23589;,
 30.00000;32.57359;30.00000;,
 16.23589;32.57359;39.19689;,
 0.00001;32.57359;42.42641;,
 -16.23587;32.57359;39.19689;,
 -29.99999;32.57359;30.00001;,
 -39.19689;32.57359;16.23589;,
 -42.42641;32.57359;0.00000;,
 -39.19689;32.57359;-16.23589;,
 -29.99999;32.57359;-30.00001;,
 -16.23586;32.57359;-39.19690;,
 -29.99999;32.57359;-30.00001;,
 0.00000;32.57359;-42.42641;,
 16.23588;32.57359;-39.19689;,
 12.75645;22.11182;-30.79680;,
 0.00000;22.11182;-33.33421;,
 23.57085;22.11182;-23.57085;,
 30.79680;22.11182;-12.75645;,
 33.33421;22.11182;0.00000;,
 30.79680;22.11182;12.75645;,
 23.57085;22.11182;23.57085;,
 12.75645;22.11182;30.79680;,
 0.00001;22.11182;33.33421;,
 -12.75644;22.11182;30.79680;,
 -23.57084;22.11182;23.57085;,
 -30.79680;22.11182;12.75645;,
 -33.33421;22.11182;0.00000;,
 -30.79680;22.11182;-12.75646;,
 -23.57084;22.11182;-23.57085;,
 -16.23586;32.57359;-39.19690;,
 -12.75643;22.11182;-30.79680;,
 8.78679;14.56722;-21.21319;,
 0.00000;14.56722;-22.96100;,
 16.23588;14.56722;-16.23588;,
 21.21319;14.56722;-8.78679;,
 22.96100;14.56722;0.00000;,
 21.21319;14.56722;8.78680;,
 16.23588;14.56722;16.23588;,
 8.78679;14.56722;21.21319;,
 0.00000;14.56722;22.96100;,
 -8.78679;14.56722;21.21320;,
 -16.23587;14.56722;16.23588;,
 -21.21319;14.56722;8.78680;,
 -22.96100;14.56722;0.00000;,
 -21.21319;14.56722;-8.78680;,
 -16.23587;14.56722;-16.23588;,
 -8.78678;14.56722;-21.21320;,
 4.47946;6.15288;-10.81438;,
 0.00000;6.15288;-11.70540;,
 8.27697;6.15288;-8.27697;,
 10.81438;6.15288;-4.47946;,
 11.70540;6.15288;0.00000;,
 10.81438;6.15288;4.47947;,
 8.27697;6.15288;8.27697;,
 4.47947;6.15288;10.81438;,
 0.00000;6.15288;11.70540;,
 -4.47946;6.15288;10.81439;,
 -8.27697;6.15288;8.27697;,
 -10.81438;6.15288;4.47947;,
 -11.70540;6.15288;0.00000;,
 -10.81438;6.15288;-4.47947;,
 -8.27697;6.15288;-8.27697;,
 -4.47946;6.15288;-10.81439;,
 0.00000;0.00000;0.00000;;
 
 256;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,9,8;,
 3;0,10,9;,
 3;0,11,10;,
 3;0,12,11;,
 3;0,13,12;,
 3;0,14,13;,
 3;0,15,14;,
 3;0,16,15;,
 3;0,2,16;,
 4;2,1,17,18;,
 4;1,3,19,17;,
 4;3,4,20,19;,
 4;4,5,21,20;,
 4;5,6,22,21;,
 4;6,7,23,22;,
 4;7,8,24,23;,
 4;8,9,25,24;,
 4;9,10,26,25;,
 4;10,11,27,26;,
 4;11,12,28,27;,
 4;12,13,29,28;,
 4;13,14,30,29;,
 4;14,15,31,30;,
 4;15,16,32,31;,
 4;16,2,18,32;,
 4;18,17,33,34;,
 4;17,19,35,33;,
 4;19,20,36,35;,
 4;20,21,37,36;,
 4;21,22,38,37;,
 4;22,23,39,38;,
 4;23,24,40,39;,
 4;24,25,41,40;,
 4;25,26,42,41;,
 4;26,27,43,42;,
 4;27,28,44,43;,
 4;28,29,45,44;,
 4;29,30,46,45;,
 4;30,31,47,46;,
 4;31,32,48,47;,
 4;32,18,34,48;,
 4;34,33,49,50;,
 4;33,35,51,49;,
 4;35,36,52,51;,
 4;36,37,53,52;,
 4;37,38,54,53;,
 4;38,39,55,54;,
 4;39,40,56,55;,
 4;40,41,57,56;,
 4;41,42,58,57;,
 4;42,43,59,58;,
 4;43,44,60,59;,
 4;44,45,61,60;,
 4;45,46,62,61;,
 4;46,47,63,62;,
 4;47,48,64,63;,
 4;48,34,50,64;,
 4;65,66,67,68;,
 4;66,69,70,67;,
 4;51,52,71,72;,
 4;52,53,73,71;,
 4;53,54,74,73;,
 4;54,55,75,74;,
 4;55,56,76,75;,
 4;56,57,77,76;,
 4;57,58,78,77;,
 4;58,59,79,78;,
 4;59,60,80,79;,
 4;60,61,81,80;,
 4;61,62,82,81;,
 4;62,63,83,82;,
 4;84,85,86,87;,
 4;85,65,68,86;,
 4;68,67,88,89;,
 4;67,70,90,88;,
 4;72,71,91,92;,
 4;71,73,93,91;,
 4;73,74,94,93;,
 4;74,75,95,94;,
 4;75,76,96,95;,
 4;76,77,97,96;,
 4;77,78,98,97;,
 4;78,79,99,98;,
 4;79,80,100,99;,
 4;80,81,101,100;,
 4;81,82,102,101;,
 4;82,83,103,102;,
 4;87,86,104,105;,
 4;86,68,89,104;,
 4;89,88,106,107;,
 4;88,90,108,106;,
 4;92,91,109,110;,
 4;91,93,111,109;,
 4;93,94,112,111;,
 4;94,95,113,112;,
 4;95,96,114,113;,
 4;96,97,115,114;,
 4;97,98,116,115;,
 4;98,99,117,116;,
 4;99,100,118,117;,
 4;100,101,119,118;,
 4;101,102,120,119;,
 4;102,103,121,120;,
 4;105,104,122,123;,
 4;104,89,107,122;,
 4;107,106,124,125;,
 4;106,108,126,124;,
 4;110,109,127,128;,
 4;109,111,129,127;,
 4;111,112,130,129;,
 4;112,113,131,130;,
 4;113,114,132,131;,
 4;114,115,133,132;,
 4;115,116,134,133;,
 4;116,117,135,134;,
 4;117,118,136,135;,
 4;118,119,137,136;,
 4;119,120,138,137;,
 4;120,121,139,138;,
 4;123,122,140,141;,
 4;122,107,125,140;,
 4;125,124,142,143;,
 4;124,126,144,142;,
 4;128,127,145,146;,
 4;127,129,147,145;,
 4;129,130,148,147;,
 4;130,131,149,148;,
 4;131,132,150,149;,
 4;132,133,151,150;,
 4;133,134,152,151;,
 4;134,135,153,152;,
 4;135,136,154,153;,
 4;136,137,155,154;,
 4;137,138,156,155;,
 4;138,139,157,156;,
 4;141,140,158,159;,
 4;140,125,143,158;,
 4;143,142,160,161;,
 4;142,144,162,160;,
 4;146,145,163,164;,
 4;145,147,165,163;,
 4;147,148,166,165;,
 4;148,149,167,166;,
 4;149,150,168,167;,
 4;150,151,169,168;,
 4;151,152,170,169;,
 4;152,153,171,170;,
 4;153,154,172,171;,
 4;154,155,173,172;,
 4;155,156,174,173;,
 4;156,157,175,174;,
 4;159,158,176,177;,
 4;158,143,161,176;,
 4;161,160,178,179;,
 4;160,162,180,178;,
 4;164,163,181,182;,
 4;163,165,183,181;,
 4;165,166,184,183;,
 4;166,167,185,184;,
 4;167,168,186,185;,
 4;168,169,187,186;,
 4;169,170,188,187;,
 4;170,171,189,188;,
 4;171,172,190,189;,
 4;172,173,191,190;,
 4;173,174,192,191;,
 4;174,175,193,192;,
 4;177,176,194,195;,
 4;176,161,179,194;,
 4;179,178,196,197;,
 4;178,180,198,196;,
 4;182,181,199,200;,
 4;181,183,201,199;,
 4;183,184,202,201;,
 4;184,185,203,202;,
 4;185,186,204,203;,
 4;186,187,205,204;,
 4;187,188,206,205;,
 4;188,189,207,206;,
 4;189,190,208,207;,
 4;190,191,209,208;,
 4;191,192,210,209;,
 4;192,193,211,210;,
 4;195,194,212,213;,
 4;194,179,197,212;,
 4;214,215,216,217;,
 4;215,200,218,216;,
 4;200,199,219,218;,
 4;199,201,220,219;,
 4;201,202,221,220;,
 4;202,203,222,221;,
 4;203,204,223,222;,
 4;204,205,224,223;,
 4;205,206,225,224;,
 4;206,207,226,225;,
 4;207,208,227,226;,
 4;208,209,228,227;,
 4;209,210,229,228;,
 4;210,211,230,229;,
 4;211,231,232,230;,
 4;231,214,217,232;,
 4;217,216,233,234;,
 4;216,218,235,233;,
 4;218,219,236,235;,
 4;219,220,237,236;,
 4;220,221,238,237;,
 4;221,222,239,238;,
 4;222,223,240,239;,
 4;223,224,241,240;,
 4;224,225,242,241;,
 4;225,226,243,242;,
 4;226,227,244,243;,
 4;227,228,245,244;,
 4;228,229,246,245;,
 4;229,230,247,246;,
 4;230,232,248,247;,
 4;232,217,234,248;,
 4;234,233,249,250;,
 4;233,235,251,249;,
 4;235,236,252,251;,
 4;236,237,253,252;,
 4;237,238,254,253;,
 4;238,239,255,254;,
 4;239,240,256,255;,
 4;240,241,257,256;,
 4;241,242,258,257;,
 4;242,243,259,258;,
 4;243,244,260,259;,
 4;244,245,261,260;,
 4;245,246,262,261;,
 4;246,247,263,262;,
 4;247,248,264,263;,
 4;248,234,250,264;,
 3;250,249,265;,
 3;249,251,265;,
 3;251,252,265;,
 3;252,253,265;,
 3;253,254,265;,
 3;254,255,265;,
 3;255,256,265;,
 3;256,257,265;,
 3;257,258,265;,
 3;258,259,265;,
 3;259,260,265;,
 3;260,261,265;,
 3;261,262,265;,
 3;262,263,265;,
 3;263,264,265;,
 3;264,250,265;;
 
 MeshMaterialList {
  3;
  256;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.000000;0.734400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/BalloonPink1_00.png";
   }
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  242;
  -0.000000;1.000000;-0.000000;,
  0.000000;0.980799;-0.195019;,
  0.074631;0.980799;-0.180174;,
  0.137900;0.980799;-0.137900;,
  0.180174;0.980799;-0.074631;,
  0.195019;0.980799;0.000000;,
  0.180174;0.980799;0.074631;,
  0.137900;0.980799;0.137900;,
  0.074631;0.980799;0.180174;,
  -0.000000;0.980799;0.195019;,
  -0.074631;0.980799;0.180174;,
  -0.137900;0.980799;0.137900;,
  -0.180174;0.980799;0.074631;,
  -0.195019;0.980799;0.000000;,
  -0.180174;0.980799;-0.074631;,
  -0.137900;0.980799;-0.137900;,
  -0.074631;0.980799;-0.180174;,
  0.000000;0.923931;-0.382560;,
  0.146400;0.923931;-0.353440;,
  0.270511;0.923930;-0.270511;,
  0.353440;0.923931;-0.146400;,
  0.382560;0.923931;0.000000;,
  0.353440;0.923931;0.146400;,
  0.270511;0.923931;0.270511;,
  0.146400;0.923931;0.353440;,
  -0.000000;0.923931;0.382560;,
  -0.146399;0.923930;0.353440;,
  -0.270511;0.923931;0.270511;,
  -0.353440;0.923931;0.146400;,
  -0.382560;0.923931;0.000000;,
  -0.353440;0.923931;-0.146400;,
  -0.270511;0.923931;-0.270511;,
  -0.146399;0.923931;-0.353440;,
  0.000000;0.850269;-0.526348;,
  0.201425;0.850269;-0.486282;,
  0.372184;0.850269;-0.372184;,
  0.486282;0.850269;-0.201425;,
  0.526348;0.850269;-0.000000;,
  0.486282;0.850269;0.201425;,
  0.372184;0.850269;0.372184;,
  0.201425;0.850269;0.486282;,
  0.000000;0.850269;0.526348;,
  -0.201425;0.850269;0.486282;,
  -0.372184;0.850269;0.372185;,
  -0.486282;0.850269;0.201425;,
  -0.526348;0.850269;0.000000;,
  -0.486282;0.850269;-0.201425;,
  -0.372184;0.850269;-0.372185;,
  -0.201425;0.850269;-0.486282;,
  0.000000;0.731430;-0.681917;,
  0.260958;0.731430;-0.630009;,
  0.482188;0.731430;-0.482188;,
  0.630009;0.731430;-0.260958;,
  0.681917;0.731430;0.000000;,
  0.630009;0.731429;0.260958;,
  0.482188;0.731430;0.482188;,
  0.260958;0.731430;0.630009;,
  0.000000;0.731430;0.681917;,
  -0.260958;0.731430;0.630009;,
  -0.482188;0.731430;0.482188;,
  -0.630009;0.731430;0.260959;,
  -0.681917;0.731430;0.000000;,
  -0.630009;0.731430;-0.260959;,
  -0.482188;0.731430;-0.482188;,
  -0.260958;0.731430;-0.630009;,
  0.000000;0.573526;-0.819187;,
  0.313489;0.573526;-0.756830;,
  0.579253;0.573526;-0.579253;,
  0.756830;0.573526;-0.313489;,
  0.819187;0.573526;0.000000;,
  0.756830;0.573526;0.313489;,
  0.579253;0.573526;0.579253;,
  0.313489;0.573526;0.756830;,
  0.000000;0.573526;0.819187;,
  -0.313489;0.573526;0.756830;,
  -0.579253;0.573526;0.579253;,
  -0.756830;0.573526;0.313490;,
  -0.819187;0.573526;0.000000;,
  -0.756830;0.573526;-0.313489;,
  -0.579253;0.573526;-0.579253;,
  -0.313489;0.573526;-0.756830;,
  0.000000;0.402778;-0.915297;,
  0.350269;0.402778;-0.845625;,
  0.647213;0.402778;-0.647213;,
  0.845625;0.402778;-0.350269;,
  0.915297;0.402779;0.000000;,
  0.845625;0.402779;0.350269;,
  0.647213;0.402779;0.647213;,
  0.350269;0.402779;0.845625;,
  0.000000;0.402779;0.915297;,
  -0.350269;0.402778;0.845625;,
  -0.647213;0.402778;0.647213;,
  -0.845625;0.402779;0.350269;,
  -0.915297;0.402779;0.000000;,
  -0.845625;0.402779;-0.350269;,
  -0.647213;0.402779;-0.647213;,
  -0.350269;0.402778;-0.845625;,
  0.000000;0.195159;-0.980772;,
  0.375325;0.195159;-0.906115;,
  0.693510;0.195159;-0.693510;,
  0.906115;0.195159;-0.375325;,
  0.980772;0.195159;-0.000000;,
  0.906115;0.195159;0.375325;,
  0.693510;0.195159;0.693510;,
  0.375325;0.195159;0.906115;,
  0.000000;0.195159;0.980772;,
  -0.375325;0.195159;0.906115;,
  -0.693510;0.195159;0.693510;,
  -0.906115;0.195159;0.375325;,
  -0.980772;0.195159;0.000000;,
  -0.906115;0.195159;-0.375325;,
  -0.693510;0.195159;-0.693510;,
  -0.375325;0.195159;-0.906115;,
  0.000000;0.000000;-1.000000;,
  0.382683;0.000000;-0.923880;,
  0.707107;0.000000;-0.707107;,
  0.923880;0.000000;-0.382683;,
  1.000000;0.000000;-0.000000;,
  0.923880;0.000000;0.382683;,
  0.707107;0.000000;0.707107;,
  0.382683;0.000000;0.923880;,
  0.000000;0.000000;1.000000;,
  -0.382683;0.000000;0.923880;,
  -0.707107;0.000000;0.707107;,
  -0.923880;0.000000;0.382684;,
  -1.000000;0.000000;0.000000;,
  -0.923879;0.000000;-0.382684;,
  -0.707106;0.000000;-0.707107;,
  -0.382683;0.000000;-0.923880;,
  0.000000;-0.195159;-0.980772;,
  0.375325;-0.195159;-0.906115;,
  0.693510;-0.195159;-0.693510;,
  0.906115;-0.195159;-0.375325;,
  0.980772;-0.195159;-0.000000;,
  0.906115;-0.195159;0.375325;,
  0.693510;-0.195159;0.693510;,
  0.375325;-0.195159;0.906115;,
  0.000000;-0.195159;0.980772;,
  -0.375325;-0.195159;0.906115;,
  -0.693510;-0.195159;0.693511;,
  -0.906115;-0.195159;0.375325;,
  -0.980772;-0.195159;0.000000;,
  -0.906115;-0.195159;-0.375325;,
  -0.693510;-0.195159;-0.693511;,
  -0.375325;-0.195159;-0.906115;,
  0.000000;-0.382803;-0.923830;,
  0.353534;-0.382803;-0.853507;,
  0.653246;-0.382804;-0.653246;,
  0.853507;-0.382803;-0.353534;,
  0.923830;-0.382804;0.000000;,
  0.853507;-0.382804;0.353534;,
  0.653246;-0.382804;0.653246;,
  0.353534;-0.382804;0.853507;,
  0.000000;-0.382803;0.923830;,
  -0.353534;-0.382803;0.853508;,
  -0.653246;-0.382803;0.653246;,
  -0.853507;-0.382804;0.353535;,
  -0.923830;-0.382804;0.000000;,
  -0.853507;-0.382804;-0.353534;,
  -0.653246;-0.382803;-0.653247;,
  -0.353534;-0.382803;-0.853508;,
  0.000000;-0.555712;-0.831375;,
  0.318153;-0.555712;-0.768090;,
  0.587871;-0.555712;-0.587871;,
  0.768090;-0.555712;-0.318153;,
  0.831375;-0.555712;0.000000;,
  0.768090;-0.555712;0.318153;,
  0.587871;-0.555712;0.587871;,
  0.318154;-0.555712;0.768090;,
  0.000000;-0.555712;0.831375;,
  -0.318153;-0.555712;0.768090;,
  -0.587871;-0.555712;0.587871;,
  -0.768090;-0.555712;0.318154;,
  -0.831375;-0.555712;0.000000;,
  -0.768090;-0.555712;-0.318154;,
  -0.587870;-0.555712;-0.587871;,
  -0.318153;-0.555712;-0.768090;,
  0.000000;-0.645251;-0.763971;,
  0.292359;-0.645250;-0.705817;,
  0.540209;-0.645250;-0.540209;,
  0.705817;-0.645250;-0.292359;,
  0.763971;-0.645250;0.000000;,
  0.705817;-0.645250;0.292359;,
  0.540209;-0.645250;0.540209;,
  0.292359;-0.645250;0.705817;,
  0.000000;-0.645250;0.763971;,
  -0.292359;-0.645251;0.705817;,
  -0.540209;-0.645251;0.540209;,
  -0.705817;-0.645250;0.292359;,
  -0.763971;-0.645250;0.000000;,
  -0.705817;-0.645250;-0.292359;,
  -0.540209;-0.645251;-0.540209;,
  -0.292359;-0.645251;-0.705817;,
  0.000000;-0.737235;-0.675636;,
  0.258555;-0.737235;-0.624206;,
  0.477747;-0.737235;-0.477747;,
  0.624206;-0.737235;-0.258555;,
  0.675636;-0.737235;-0.000000;,
  0.624206;-0.737235;0.258555;,
  0.477747;-0.737235;0.477747;,
  0.258555;-0.737235;0.624206;,
  0.000000;-0.737235;0.675636;,
  -0.258555;-0.737235;0.624206;,
  -0.477747;-0.737235;0.477747;,
  -0.624206;-0.737235;0.258555;,
  -0.675636;-0.737235;0.000000;,
  -0.624206;-0.737235;-0.258555;,
  -0.477747;-0.737235;-0.477747;,
  -0.258555;-0.737235;-0.624206;,
  0.000000;-0.804844;-0.593486;,
  0.227117;-0.804844;-0.548310;,
  0.419658;-0.804844;-0.419658;,
  0.548310;-0.804844;-0.227117;,
  0.593486;-0.804844;-0.000000;,
  0.548310;-0.804844;0.227117;,
  0.419658;-0.804844;0.419658;,
  0.227117;-0.804844;0.548310;,
  0.000000;-0.804844;0.593486;,
  -0.227117;-0.804844;0.548310;,
  -0.419658;-0.804844;0.419658;,
  -0.548309;-0.804844;0.227117;,
  -0.593486;-0.804844;0.000000;,
  -0.548309;-0.804844;-0.227117;,
  -0.419658;-0.804844;-0.419658;,
  -0.227117;-0.804844;-0.548310;,
  0.000000;-0.845744;-0.533589;,
  0.204195;-0.845744;-0.492972;,
  0.377304;-0.845744;-0.377304;,
  0.492972;-0.845744;-0.204195;,
  0.533589;-0.845744;-0.000000;,
  0.492972;-0.845744;0.204195;,
  0.377304;-0.845744;0.377304;,
  0.204195;-0.845744;0.492972;,
  0.000000;-0.845744;0.533589;,
  -0.204195;-0.845744;0.492971;,
  -0.377304;-0.845744;0.377304;,
  -0.492971;-0.845744;0.204196;,
  -0.533589;-0.845744;0.000000;,
  -0.492971;-0.845744;-0.204196;,
  -0.377304;-0.845744;-0.377304;,
  -0.204195;-0.845744;-0.492972;,
  0.000000;-1.000000;-0.000000;;
  256;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,12,11;,
  3;0,13,12;,
  3;0,14,13;,
  3;0,15,14;,
  3;0,16,15;,
  3;0,1,16;,
  4;1,2,18,17;,
  4;2,3,19,18;,
  4;3,4,20,19;,
  4;4,5,21,20;,
  4;5,6,22,21;,
  4;6,7,23,22;,
  4;7,8,24,23;,
  4;8,9,25,24;,
  4;9,10,26,25;,
  4;10,11,27,26;,
  4;11,12,28,27;,
  4;12,13,29,28;,
  4;13,14,30,29;,
  4;14,15,31,30;,
  4;15,16,32,31;,
  4;16,1,17,32;,
  4;17,18,34,33;,
  4;18,19,35,34;,
  4;19,20,36,35;,
  4;20,21,37,36;,
  4;21,22,38,37;,
  4;22,23,39,38;,
  4;23,24,40,39;,
  4;24,25,41,40;,
  4;25,26,42,41;,
  4;26,27,43,42;,
  4;27,28,44,43;,
  4;28,29,45,44;,
  4;29,30,46,45;,
  4;30,31,47,46;,
  4;31,32,48,47;,
  4;32,17,33,48;,
  4;33,34,50,49;,
  4;34,35,51,50;,
  4;35,36,52,51;,
  4;36,37,53,52;,
  4;37,38,54,53;,
  4;38,39,55,54;,
  4;39,40,56,55;,
  4;40,41,57,56;,
  4;41,42,58,57;,
  4;42,43,59,58;,
  4;43,44,60,59;,
  4;44,45,61,60;,
  4;45,46,62,61;,
  4;46,47,63,62;,
  4;47,48,64,63;,
  4;48,33,49,64;,
  4;49,50,66,65;,
  4;50,51,67,66;,
  4;51,52,68,67;,
  4;52,53,69,68;,
  4;53,54,70,69;,
  4;54,55,71,70;,
  4;55,56,72,71;,
  4;56,57,73,72;,
  4;57,58,74,73;,
  4;58,59,75,74;,
  4;59,60,76,75;,
  4;60,61,77,76;,
  4;61,62,78,77;,
  4;62,63,79,78;,
  4;63,64,80,79;,
  4;64,49,65,80;,
  4;65,66,82,81;,
  4;66,67,83,82;,
  4;67,68,84,83;,
  4;68,69,85,84;,
  4;69,70,86,85;,
  4;70,71,87,86;,
  4;71,72,88,87;,
  4;72,73,89,88;,
  4;73,74,90,89;,
  4;74,75,91,90;,
  4;75,76,92,91;,
  4;76,77,93,92;,
  4;77,78,94,93;,
  4;78,79,95,94;,
  4;79,80,96,95;,
  4;80,65,81,96;,
  4;81,82,98,97;,
  4;82,83,99,98;,
  4;83,84,100,99;,
  4;84,85,101,100;,
  4;85,86,102,101;,
  4;86,87,103,102;,
  4;87,88,104,103;,
  4;88,89,105,104;,
  4;89,90,106,105;,
  4;90,91,107,106;,
  4;91,92,108,107;,
  4;92,93,109,108;,
  4;93,94,110,109;,
  4;94,95,111,110;,
  4;95,96,112,111;,
  4;96,81,97,112;,
  4;97,98,114,113;,
  4;98,99,115,114;,
  4;99,100,116,115;,
  4;100,101,117,116;,
  4;101,102,118,117;,
  4;102,103,119,118;,
  4;103,104,120,119;,
  4;104,105,121,120;,
  4;105,106,122,121;,
  4;106,107,123,122;,
  4;107,108,124,123;,
  4;108,109,125,124;,
  4;109,110,126,125;,
  4;110,111,127,126;,
  4;111,112,128,127;,
  4;112,97,113,128;,
  4;113,114,130,129;,
  4;114,115,131,130;,
  4;115,116,132,131;,
  4;116,117,133,132;,
  4;117,118,134,133;,
  4;118,119,135,134;,
  4;119,120,136,135;,
  4;120,121,137,136;,
  4;121,122,138,137;,
  4;122,123,139,138;,
  4;123,124,140,139;,
  4;124,125,141,140;,
  4;125,126,142,141;,
  4;126,127,143,142;,
  4;127,128,144,143;,
  4;128,113,129,144;,
  4;129,130,146,145;,
  4;130,131,147,146;,
  4;131,132,148,147;,
  4;132,133,149,148;,
  4;133,134,150,149;,
  4;134,135,151,150;,
  4;135,136,152,151;,
  4;136,137,153,152;,
  4;137,138,154,153;,
  4;138,139,155,154;,
  4;139,140,156,155;,
  4;140,141,157,156;,
  4;141,142,158,157;,
  4;142,143,159,158;,
  4;143,144,160,159;,
  4;144,129,145,160;,
  4;145,146,162,161;,
  4;146,147,163,162;,
  4;147,148,164,163;,
  4;148,149,165,164;,
  4;149,150,166,165;,
  4;150,151,167,166;,
  4;151,152,168,167;,
  4;152,153,169,168;,
  4;153,154,170,169;,
  4;154,155,171,170;,
  4;155,156,172,171;,
  4;156,157,173,172;,
  4;157,158,174,173;,
  4;158,159,175,174;,
  4;159,160,176,175;,
  4;160,145,161,176;,
  4;161,162,178,177;,
  4;162,163,179,178;,
  4;163,164,180,179;,
  4;164,165,181,180;,
  4;165,166,182,181;,
  4;166,167,183,182;,
  4;167,168,184,183;,
  4;168,169,185,184;,
  4;169,170,186,185;,
  4;170,171,187,186;,
  4;171,172,188,187;,
  4;172,173,189,188;,
  4;173,174,190,189;,
  4;174,175,191,190;,
  4;175,176,192,191;,
  4;176,161,177,192;,
  4;177,178,194,193;,
  4;178,179,195,194;,
  4;179,180,196,195;,
  4;180,181,197,196;,
  4;181,182,198,197;,
  4;182,183,199,198;,
  4;183,184,200,199;,
  4;184,185,201,200;,
  4;185,186,202,201;,
  4;186,187,203,202;,
  4;187,188,204,203;,
  4;188,189,205,204;,
  4;189,190,206,205;,
  4;190,191,207,206;,
  4;191,192,208,207;,
  4;192,177,193,208;,
  4;193,194,210,209;,
  4;194,195,211,210;,
  4;195,196,212,211;,
  4;196,197,213,212;,
  4;197,198,214,213;,
  4;198,199,215,214;,
  4;199,200,216,215;,
  4;200,201,217,216;,
  4;201,202,218,217;,
  4;202,203,219,218;,
  4;203,204,220,219;,
  4;204,205,221,220;,
  4;205,206,222,221;,
  4;206,207,223,222;,
  4;207,208,224,223;,
  4;208,193,209,224;,
  4;209,210,226,225;,
  4;210,211,227,226;,
  4;211,212,228,227;,
  4;212,213,229,228;,
  4;213,214,230,229;,
  4;214,215,231,230;,
  4;215,216,232,231;,
  4;216,217,233,232;,
  4;217,218,234,233;,
  4;218,219,235,234;,
  4;219,220,236,235;,
  4;220,221,237,236;,
  4;221,222,238,237;,
  4;222,223,239,238;,
  4;223,224,240,239;,
  4;224,209,225,240;,
  3;225,226,241;,
  3;226,227,241;,
  3;227,228,241;,
  3;228,229,241;,
  3;229,230,241;,
  3;230,231,241;,
  3;231,232,241;,
  3;232,233,241;,
  3;233,234,241;,
  3;234,235,241;,
  3;235,236,241;,
  3;236,237,241;,
  3;237,238,241;,
  3;238,239,241;,
  3;239,240,241;,
  3;240,225,241;;
 }
 MeshTextureCoords {
  266;
  0.500000;0.903340;,
  0.510670;0.906090;,
  0.500000;0.906090;,
  0.519720;0.906090;,
  0.525770;0.906090;,
  0.527890;0.906090;,
  0.525770;0.906090;,
  0.519720;0.906090;,
  0.510670;0.906090;,
  0.500000;0.906090;,
  0.489330;0.906090;,
  0.480280;0.906090;,
  0.474230;0.906090;,
  0.472110;0.906090;,
  0.474230;0.906090;,
  0.480280;0.906090;,
  0.489330;0.906090;,
  0.520940;0.914230;,
  0.500000;0.914230;,
  0.538690;0.914230;,
  0.550550;0.914230;,
  0.554720;0.914230;,
  0.550550;0.914230;,
  0.538690;0.914230;,
  0.520940;0.914230;,
  0.500000;0.914230;,
  0.479060;0.914230;,
  0.461310;0.914230;,
  0.449450;0.914230;,
  0.445280;0.914230;,
  0.449450;0.914230;,
  0.461310;0.914230;,
  0.479060;0.914230;,
  0.530400;0.927440;,
  0.500000;0.927440;,
  0.556170;0.927440;,
  0.573390;0.927440;,
  0.579440;0.927440;,
  0.573390;0.927440;,
  0.556170;0.927440;,
  0.530400;0.927440;,
  0.500000;0.927440;,
  0.469600;0.927440;,
  0.443830;0.927440;,
  0.426610;0.927440;,
  0.420560;0.927440;,
  0.426610;0.927440;,
  0.443830;0.927440;,
  0.469600;0.927440;,
  0.538690;0.945220;,
  0.500000;0.945220;,
  0.571490;0.945220;,
  0.593410;0.945220;,
  0.601110;0.945220;,
  0.593410;0.945220;,
  0.571490;0.945220;,
  0.538690;0.945220;,
  0.500000;0.945220;,
  0.461310;0.945220;,
  0.428510;0.945220;,
  0.406590;0.945220;,
  0.398890;0.945220;,
  0.406590;0.945220;,
  0.428510;0.945220;,
  0.461310;0.945220;,
  0.549336;0.200053;,
  0.665976;0.200053;,
  0.686490;0.265372;,
  0.549336;0.265372;,
  0.764859;0.200053;,
  0.802764;0.265372;,
  0.609840;0.966890;,
  0.584070;0.966890;,
  0.618890;0.966890;,
  0.609840;0.966890;,
  0.584070;0.966890;,
  0.545500;0.966890;,
  0.500000;0.966890;,
  0.454500;0.966890;,
  0.415930;0.966890;,
  0.390160;0.966890;,
  0.381110;0.966890;,
  0.390160;0.966890;,
  0.415930;0.966890;,
  0.333814;0.200053;,
  0.432696;0.200053;,
  0.412182;0.265372;,
  0.295908;0.265372;,
  0.701734;0.332710;,
  0.549336;0.332710;,
  0.830930;0.332710;,
  0.622040;0.991610;,
  0.593410;0.991610;,
  0.632100;0.991610;,
  0.622040;0.991610;,
  0.593410;0.991610;,
  0.550550;0.991610;,
  0.500000;0.991610;,
  0.449450;0.991610;,
  0.406590;0.991610;,
  0.377960;0.991610;,
  0.367900;0.991610;,
  0.377960;0.991610;,
  0.406590;0.991610;,
  0.396939;0.332710;,
  0.267742;0.332710;,
  0.711121;0.413571;,
  0.549336;0.413571;,
  0.848275;0.413571;,
  0.629560;1.018430;,
  0.599160;1.018430;,
  0.640240;1.018430;,
  0.629560;1.018430;,
  0.599160;1.018430;,
  0.553670;1.018430;,
  0.500000;1.018430;,
  0.446330;1.018430;,
  0.400840;1.018430;,
  0.370440;1.018430;,
  0.359760;1.018430;,
  0.370440;1.018430;,
  0.400840;1.018430;,
  0.387552;0.413571;,
  0.250398;0.413571;,
  0.714290;0.497664;,
  0.549336;0.497664;,
  0.854131;0.497664;,
  0.632100;1.046330;,
  0.601110;1.046330;,
  0.642980;1.046330;,
  0.632100;1.046330;,
  0.601110;1.046330;,
  0.554720;1.046330;,
  0.500000;1.046330;,
  0.445280;1.046330;,
  0.398890;1.046330;,
  0.367900;1.046330;,
  0.357020;1.046330;,
  0.367900;1.046330;,
  0.398890;1.046330;,
  0.384383;0.497664;,
  0.244541;0.497664;,
  0.711121;0.581757;,
  0.549336;0.581757;,
  0.848275;0.581757;,
  0.629560;1.074220;,
  0.599160;1.074220;,
  0.640240;1.074220;,
  0.629560;1.074220;,
  0.599160;1.074220;,
  0.553670;1.074220;,
  0.500000;1.074220;,
  0.446330;1.074220;,
  0.400840;1.074220;,
  0.370440;1.074220;,
  0.359760;1.074220;,
  0.370440;1.074220;,
  0.400840;1.074220;,
  0.387552;0.581757;,
  0.250398;0.581757;,
  0.701734;0.662618;,
  0.549336;0.662618;,
  0.830930;0.662618;,
  0.622040;1.101040;,
  0.593410;1.101040;,
  0.632100;1.101040;,
  0.622040;1.101040;,
  0.593410;1.101040;,
  0.550550;1.101040;,
  0.500000;1.101040;,
  0.449450;1.101040;,
  0.406590;1.101040;,
  0.377960;1.101040;,
  0.367900;1.101040;,
  0.377960;1.101040;,
  0.406590;1.101040;,
  0.396939;0.662618;,
  0.267742;0.662618;,
  0.686490;0.737140;,
  0.549336;0.737140;,
  0.802764;0.737140;,
  0.609840;1.125760;,
  0.584070;1.125760;,
  0.618890;1.125760;,
  0.609840;1.125760;,
  0.584070;1.125760;,
  0.545500;1.125760;,
  0.500000;1.125760;,
  0.454500;1.125760;,
  0.415930;1.125760;,
  0.390160;1.125760;,
  0.381110;1.125760;,
  0.390160;1.125760;,
  0.415930;1.125760;,
  0.412182;0.737140;,
  0.295908;0.737140;,
  0.665976;0.802459;,
  0.549336;0.802459;,
  0.764859;0.802459;,
  0.593410;1.147430;,
  0.571490;1.147430;,
  0.601110;1.147430;,
  0.593410;1.147430;,
  0.571490;1.147430;,
  0.538690;1.147430;,
  0.500000;1.147430;,
  0.461310;1.147430;,
  0.428510;1.147430;,
  0.406590;1.147430;,
  0.398890;1.147430;,
  0.406590;1.147430;,
  0.428510;1.147430;,
  0.432696;0.802459;,
  0.333814;0.802459;,
  0.500000;1.147430;,
  0.538690;1.147430;,
  0.530400;1.165210;,
  0.500000;1.165210;,
  0.556170;1.165210;,
  0.573390;1.165210;,
  0.579440;1.165210;,
  0.573390;1.165210;,
  0.556170;1.165210;,
  0.530400;1.165210;,
  0.500000;1.165210;,
  0.469600;1.165210;,
  0.443830;1.165210;,
  0.426610;1.165210;,
  0.420560;1.165210;,
  0.426610;1.165210;,
  0.443830;1.165210;,
  0.461310;1.147430;,
  0.469600;1.165210;,
  0.520940;1.178430;,
  0.500000;1.178430;,
  0.538690;1.178430;,
  0.550550;1.178430;,
  0.554720;1.178430;,
  0.550550;1.178430;,
  0.538690;1.178430;,
  0.520940;1.178430;,
  0.500000;1.178430;,
  0.479060;1.178430;,
  0.461310;1.178430;,
  0.449450;1.178430;,
  0.445280;1.178430;,
  0.449450;1.178430;,
  0.461310;1.178430;,
  0.479060;1.178430;,
  0.510670;1.186560;,
  0.500000;1.186560;,
  0.519720;1.186560;,
  0.525770;1.186560;,
  0.527890;1.186560;,
  0.525770;1.186560;,
  0.519720;1.186560;,
  0.510670;1.186560;,
  0.500000;1.186560;,
  0.489330;1.186560;,
  0.480280;1.186560;,
  0.474230;1.186560;,
  0.472110;1.186560;,
  0.474230;1.186560;,
  0.480280;1.186560;,
  0.489330;1.186560;,
  0.500000;1.189310;;
 }
}
