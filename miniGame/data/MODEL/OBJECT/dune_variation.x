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
 256;
 -0.00865;20.69799;-4.30461;,
 -0.00865;21.80156;0.00000;,
 3.68537;20.69799;-2.00337;,
 -0.00865;20.69799;4.30461;,
 -4.16060;20.69799;-0.59338;,
 28.69501;9.97908;-2.00337;,
 -0.00865;9.97908;-20.00239;,
 -29.17024;9.97908;-0.59338;,
 47.57922;0.48924;-2.00336;,
 -0.00865;0.48924;-32.61043;,
 -48.48731;0.48924;0.00531;,
 -10.11472;17.65096;4.76567;,
 -27.61683;9.52427;7.14899;,
 -0.00865;9.97908;20.00239;,
 -5.31271;19.99665;2.70062;,
 -30.31426;9.26580;2.72332;,
 -48.70476;0.30847;5.23853;,
 -0.00865;0.48924;32.61043;,
 -49.19039;0.24592;2.74602;,
 5.17648;21.16085;0.30628;,
 30.18075;10.43401;0.32136;,
 4.28008;21.16085;2.23699;,
 29.79450;10.43401;2.86716;,
 49.05958;0.93622;0.33644;,
 48.56501;0.93622;1.91127;,
 -17.28486;26.11946;-6.88169;,
 -9.20954;30.56483;-6.88169;,
 -7.11919;26.26592;-17.84506;,
 -26.06097;17.33839;-14.06341;,
 -1.10804;33.41073;-6.88169;,
 -0.43322;26.26592;-17.84506;,
 5.57791;34.76499;-6.88169;,
 6.25274;26.26592;-17.84506;,
 14.11175;36.02535;-6.88169;,
 17.75645;26.26592;-17.84506;,
 19.80188;30.24704;-10.22903;,
 24.38809;26.26592;-9.96347;,
 -8.07376;19.37906;-25.87676;,
 -33.02929;11.18717;-20.55675;,
 -0.61241;19.37906;-25.87676;,
 6.84894;19.37906;-25.87676;,
 19.68675;19.37906;-25.87676;,
 30.05038;18.56766;-18.44314;,
 -25.17673;10.05237;-32.61646;,
 -38.30810;6.54803;-24.52979;,
 -0.61241;10.05237;-32.61646;,
 6.84894;10.05237;-32.61646;,
 19.68675;10.05237;-32.63502;,
 34.56613;10.11919;-26.64593;,
 -27.68057;0.21437;-39.38982;,
 -39.79825;-0.18237;-32.11736;,
 -1.12241;-0.03068;-42.95773;,
 9.10037;-0.17485;-40.89133;,
 31.48469;0.10572;-43.92657;,
 37.48876;0.01584;-36.87091;,
 18.32167;32.29766;10.88669;,
 13.30637;34.67387;10.88669;,
 12.93869;26.26592;20.11225;,
 24.38809;26.26592;13.81259;,
 4.77254;33.41352;10.88669;,
 6.68318;26.11264;20.70811;,
 -1.91342;32.05927;10.88669;,
 -0.43322;26.26592;19.97173;,
 -10.01494;29.21338;10.88669;,
 -7.11919;24.47429;18.32017;,
 -18.09025;24.76798;10.88669;,
 -26.06097;17.33839;16.75000;,
 12.93869;18.47214;24.80440;,
 31.16077;19.37906;16.16831;,
 6.25274;18.47214;24.28767;,
 -0.43322;18.47214;23.44913;,
 -6.35293;17.60233;23.47587;,
 -32.26303;10.31736;19.70331;,
 16.16404;9.69447;33.43214;,
 34.61649;10.05237;20.07441;,
 6.84894;10.05237;30.83976;,
 -0.61241;10.05237;29.89460;,
 -23.96778;8.54985;29.18954;,
 -33.85500;6.44726;28.59341;,
 18.79431;0.03571;42.01956;,
 37.48876;0.72567;27.16288;,
 6.84894;0.01325;45.74627;,
 -4.50416;-0.03669;48.32571;,
 -26.58062;0.72567;44.66510;,
 -38.36710;0.25695;32.19695;,
 29.09988;27.37259;-2.31155;,
 23.47966;33.82553;-2.53230;,
 34.91502;19.66712;-1.48159;,
 39.78037;11.51881;-1.08914;,
 45.65983;-0.00100;-1.22365;,
 -25.00536;20.84093;-0.81179;,
 -18.17806;28.75268;-0.81179;,
 -34.95383;13.37220;-1.35749;,
 -40.26210;8.70630;-1.23094;,
 -52.86687;0.99150;-11.97634;,
 -9.65778;33.03022;-0.81179;,
 -1.17000;34.22161;-0.81179;,
 5.77177;37.00721;-0.81179;,
 15.17340;38.16334;-0.81179;,
 0.04041;24.35329;0.17187;,
 1.16797;23.66174;-2.01789;,
 0.04041;23.66174;-2.29581;,
 2.03722;23.66174;-1.24780;,
 2.44902;23.66174;-0.16196;,
 2.30904;23.66174;0.99088;,
 1.64935;23.66174;1.94662;,
 0.62106;23.66174;2.48630;,
 -0.54025;23.66174;2.48630;,
 -1.56853;23.66174;1.94662;,
 -2.22823;23.66174;0.99088;,
 -2.36821;23.66174;-0.16196;,
 -1.95640;23.66174;-1.24780;,
 -1.08715;23.66174;-2.01789;,
 2.51371;22.45843;-4.56996;,
 0.04041;22.45843;-5.17958;,
 4.42041;22.45843;-2.88077;,
 5.32370;22.45843;-0.49899;,
 5.01666;22.45843;2.02976;,
 3.56961;22.45843;4.12617;,
 1.31407;22.45843;5.30997;,
 -1.23325;22.45843;5.30997;,
 -3.48880;22.45843;4.12617;,
 -4.93584;22.45843;2.02976;,
 -5.24289;22.45843;-0.49899;,
 -4.33959;22.45843;-2.88077;,
 -2.43289;22.45843;-4.56996;,
 3.58455;20.80233;-6.60536;,
 0.04041;20.80233;-7.47891;,
 6.31677;20.80233;-4.18482;,
 7.61115;20.80233;-0.77181;,
 7.17117;20.80233;2.85179;,
 5.09762;20.80233;5.85586;,
 1.86551;20.80233;7.55220;,
 -1.78470;20.80233;7.55220;,
 -5.01680;20.80233;5.85586;,
 -7.09036;20.80233;2.85179;,
 -7.53034;20.80233;-0.77181;,
 -6.23596;20.80233;-4.18482;,
 -3.50373;20.80233;-6.60536;,
 4.60621;19.37320;-8.54637;,
 0.04041;19.37320;-9.67174;,
 8.12604;19.37320;-5.42807;,
 9.79355;19.37320;-1.03121;,
 9.22673;19.37320;3.63695;,
 6.55544;19.37320;7.50699;,
 2.39163;19.37320;9.69232;,
 -2.31081;19.37320;9.69232;,
 -6.47463;19.37320;7.50700;,
 -9.14591;19.37320;3.63695;,
 -9.71274;19.37320;-1.03121;,
 -8.04522;19.37320;-5.42807;,
 -4.52539;19.37320;-8.54638;,
 5.45150;17.93089;-10.15402;,
 0.04041;17.96151;-11.48774;,
 9.62299;17.93089;-6.45841;,
 11.59921;17.93089;-1.24753;,
 10.92746;17.93089;4.28488;,
 7.76160;17.93089;8.87139;,
 2.82693;17.93089;11.46132;,
 -2.74611;17.93089;11.46132;,
 -7.68079;17.96151;8.87139;,
 -10.84664;17.96151;4.28488;,
 -11.51839;17.96151;-1.24753;,
 -9.54217;17.96151;-6.45841;,
 -5.37069;17.96151;-10.15403;,
 6.29343;16.05561;-11.75193;,
 0.04041;16.05561;-13.29316;,
 11.11396;16.05561;-7.48131;,
 13.39768;16.05561;-1.45965;,
 12.62139;16.05561;4.93355;,
 8.96296;16.05561;10.23370;,
 3.26049;16.05561;13.22660;,
 -3.17967;16.05561;13.22660;,
 -8.88215;16.05561;10.23370;,
 -12.54058;16.05561;4.93356;,
 -13.31686;16.05561;-1.45965;,
 -11.03315;16.05561;-7.48131;,
 -6.21261;16.05561;-11.75193;,
 7.38543;14.55173;-12.86635;,
 -0.45483;14.55173;-14.79882;,
 12.58512;14.62382;-8.36633;,
 15.22782;13.88866;-1.47023;,
 14.35564;13.88866;5.71277;,
 10.24527;13.88866;11.66768;,
 3.83832;13.88866;15.03032;,
 -3.39744;13.88866;15.03032;,
 -9.80439;13.88866;11.66768;,
 -13.91477;13.88866;5.71277;,
 -15.23937;14.39731;-1.51699;,
 -12.37596;14.39731;-9.06715;,
 -6.33180;14.39731;-14.42181;,
 7.92190;12.71005;-14.97334;,
 0.00000;12.71005;-16.92592;,
 14.02901;12.71005;-9.56293;,
 16.92222;12.71005;-1.93413;,
 15.93876;12.71005;6.16537;,
 11.30393;12.71005;12.88010;,
 4.07950;12.71005;16.67177;,
 -4.07950;12.71005;16.67177;,
 -11.30393;12.71005;12.88010;,
 -15.93876;12.71005;6.16537;,
 -16.92222;12.71005;-1.93414;,
 -14.02901;12.71005;-9.56293;,
 -7.92189;12.71005;-14.97334;,
 8.91046;10.63743;-16.83479;,
 0.00000;10.63743;-19.03102;,
 15.77965;10.63743;-10.74921;,
 19.03391;10.63743;-2.16844;,
 17.92773;10.63743;6.94178;,
 12.71452;10.63743;14.49441;,
 4.58857;10.63743;18.75924;,
 -5.06354;10.83828;20.77417;,
 -13.90871;11.04894;15.26172;,
 -17.92773;10.63743;6.94179;,
 -19.03391;10.63743;-2.16844;,
 -15.77965;10.63743;-10.74922;,
 -8.91046;10.63743;-16.83480;,
 11.34800;7.67987;-21.40587;,
 0.00000;7.67987;-24.20290;,
 20.09631;7.67987;-13.65553;,
 24.24080;7.67987;-2.72742;,
 22.83200;7.67987;8.87497;,
 16.19268;7.67987;18.49371;,
 5.84381;7.67987;23.92522;,
 -5.84381;7.67987;23.92522;,
 -16.19268;7.67987;18.49371;,
 -22.83200;7.67987;8.87498;,
 -24.24080;7.67987;-2.72743;,
 -20.09631;7.67987;-13.65554;,
 -11.34799;7.67987;-21.40587;,
 12.76018;6.04841;-24.04909;,
 0.00000;6.04841;-27.19416;,
 22.59715;6.04841;-15.33427;,
 27.25739;6.04841;-3.04622;,
 25.67329;6.04841;10.00003;,
 18.20776;6.04841;20.81572;,
 6.57103;6.04841;26.92315;,
 -6.57103;6.04841;26.92315;,
 -18.20775;6.04841;20.81572;,
 -25.67329;6.04841;10.00003;,
 -27.25739;6.04841;-3.04622;,
 -22.59714;6.04841;-15.33427;,
 -12.76016;6.04841;-24.04910;,
 16.00458;4.41433;-30.11776;,
 0.00000;4.41433;-34.06254;,
 28.34271;4.41433;-19.18712;,
 34.18785;4.41433;-3.77471;,
 32.20098;4.41433;12.58867;,
 22.83727;4.41433;26.15439;,
 8.24178;4.41433;33.81469;,
 -8.24178;4.41433;33.81469;,
 -22.83727;4.41433;26.15439;,
 -32.20098;4.41433;12.58867;,
 -34.18785;4.41433;-3.77471;,
 -28.34271;4.41433;-19.18712;,
 -16.00456;4.41433;-30.11776;;
 
 244;
 3;0,1,2;,
 3;2,1,3;,
 3;3,1,4;,
 3;4,1,0;,
 4;5,6,0,2;,
 4;6,7,4,0;,
 4;8,9,6,5;,
 4;9,10,7,6;,
 4;11,12,13,3;,
 4;14,11,3,4;,
 4;15,14,4,7;,
 4;15,12,11,14;,
 4;12,16,17,13;,
 4;18,15,7,10;,
 4;18,16,12,15;,
 4;19,20,5,2;,
 4;21,19,2,3;,
 4;22,21,3,13;,
 4;22,20,19,21;,
 4;20,23,8,5;,
 4;24,22,13,17;,
 4;24,23,20,22;,
 4;25,26,27,28;,
 4;26,29,30,27;,
 4;29,31,32,30;,
 4;31,33,34,32;,
 4;33,35,36,34;,
 4;28,27,37,38;,
 4;27,30,39,37;,
 4;30,32,40,39;,
 4;32,34,41,40;,
 4;34,36,42,41;,
 4;38,37,43,44;,
 4;37,39,45,43;,
 4;39,40,46,45;,
 4;40,41,47,46;,
 4;41,42,48,47;,
 4;44,43,49,50;,
 4;43,45,51,49;,
 4;45,46,52,51;,
 4;46,47,53,52;,
 4;47,48,54,53;,
 4;55,56,57,58;,
 4;56,59,60,57;,
 4;59,61,62,60;,
 4;61,63,64,62;,
 4;63,65,66,64;,
 4;58,57,67,68;,
 4;57,60,69,67;,
 4;60,62,70,69;,
 4;62,64,71,70;,
 4;64,66,72,71;,
 4;68,67,73,74;,
 4;67,69,75,73;,
 4;69,70,76,75;,
 4;70,71,77,76;,
 4;71,72,78,77;,
 4;74,73,79,80;,
 4;73,75,81,79;,
 4;75,76,82,81;,
 4;76,77,83,82;,
 4;77,78,84,83;,
 4;85,86,55,58;,
 4;86,85,36,35;,
 4;87,85,58,68;,
 4;85,87,42,36;,
 4;88,87,68,74;,
 4;87,88,48,42;,
 4;89,88,74,80;,
 4;88,89,54,48;,
 4;90,91,25,28;,
 4;91,90,66,65;,
 4;92,90,28,38;,
 4;90,92,72,66;,
 4;93,92,38,44;,
 4;92,93,78,72;,
 4;94,93,44,50;,
 4;93,94,84,78;,
 4;95,91,65,63;,
 4;91,95,26,25;,
 4;96,95,63,61;,
 4;95,96,29,26;,
 4;97,96,61,59;,
 4;96,97,31,29;,
 4;98,97,59,56;,
 4;97,98,33,31;,
 4;86,98,56,55;,
 4;98,86,35,33;,
 3;99,100,101;,
 3;99,102,100;,
 3;99,103,102;,
 3;99,104,103;,
 3;99,105,104;,
 3;99,106,105;,
 3;99,107,106;,
 3;99,108,107;,
 3;99,109,108;,
 3;99,110,109;,
 3;99,111,110;,
 3;99,112,111;,
 3;99,101,112;,
 4;101,100,113,114;,
 4;100,102,115,113;,
 4;102,103,116,115;,
 4;103,104,117,116;,
 4;104,105,118,117;,
 4;105,106,119,118;,
 4;106,107,120,119;,
 4;107,108,121,120;,
 4;108,109,122,121;,
 4;109,110,123,122;,
 4;110,111,124,123;,
 4;111,112,125,124;,
 4;112,101,114,125;,
 4;114,113,126,127;,
 4;113,115,128,126;,
 4;115,116,129,128;,
 4;116,117,130,129;,
 4;117,118,131,130;,
 4;118,119,132,131;,
 4;119,120,133,132;,
 4;120,121,134,133;,
 4;121,122,135,134;,
 4;122,123,136,135;,
 4;123,124,137,136;,
 4;124,125,138,137;,
 4;125,114,127,138;,
 4;127,126,139,140;,
 4;126,128,141,139;,
 4;128,129,142,141;,
 4;129,130,143,142;,
 4;130,131,144,143;,
 4;131,132,145,144;,
 4;132,133,146,145;,
 4;133,134,147,146;,
 4;134,135,148,147;,
 4;135,136,149,148;,
 4;136,137,150,149;,
 4;137,138,151,150;,
 4;138,127,140,151;,
 4;140,139,152,153;,
 4;139,141,154,152;,
 4;141,142,155,154;,
 4;142,143,156,155;,
 4;143,144,157,156;,
 4;144,145,158,157;,
 4;145,146,159,158;,
 4;146,147,160,159;,
 4;147,148,161,160;,
 4;148,149,162,161;,
 4;149,150,163,162;,
 4;150,151,164,163;,
 4;151,140,153,164;,
 4;153,152,165,166;,
 4;152,154,167,165;,
 4;154,155,168,167;,
 4;155,156,169,168;,
 4;156,157,170,169;,
 4;157,158,171,170;,
 4;158,159,172,171;,
 4;159,160,173,172;,
 4;160,161,174,173;,
 4;161,162,175,174;,
 4;162,163,176,175;,
 4;163,164,177,176;,
 4;164,153,166,177;,
 4;166,165,178,179;,
 4;165,167,180,178;,
 4;167,168,181,180;,
 4;168,169,182,181;,
 4;169,170,183,182;,
 4;170,171,184,183;,
 4;171,172,185,184;,
 4;172,173,186,185;,
 4;173,174,187,186;,
 4;174,175,188,187;,
 4;175,176,189,188;,
 4;176,177,190,189;,
 4;177,166,179,190;,
 4;179,178,191,192;,
 4;178,180,193,191;,
 4;180,181,194,193;,
 4;181,182,195,194;,
 4;182,183,196,195;,
 4;183,184,197,196;,
 4;184,185,198,197;,
 4;185,186,199,198;,
 4;186,187,200,199;,
 4;187,188,201,200;,
 4;188,189,202,201;,
 4;189,190,203,202;,
 4;190,179,192,203;,
 4;192,191,204,205;,
 4;191,193,206,204;,
 4;193,194,207,206;,
 4;194,195,208,207;,
 4;195,196,209,208;,
 4;196,197,210,209;,
 4;197,198,211,210;,
 4;198,199,212,211;,
 4;199,200,213,212;,
 4;200,201,214,213;,
 4;201,202,215,214;,
 4;202,203,216,215;,
 4;203,192,205,216;,
 4;205,204,217,218;,
 4;204,206,219,217;,
 4;206,207,220,219;,
 4;207,208,221,220;,
 4;208,209,222,221;,
 4;209,210,223,222;,
 4;210,211,224,223;,
 4;211,212,225,224;,
 4;212,213,226,225;,
 4;213,214,227,226;,
 4;214,215,228,227;,
 4;215,216,229,228;,
 4;216,205,218,229;,
 4;218,217,230,231;,
 4;217,219,232,230;,
 4;219,220,233,232;,
 4;220,221,234,233;,
 4;221,222,235,234;,
 4;222,223,236,235;,
 4;223,224,237,236;,
 4;224,225,238,237;,
 4;225,226,239,238;,
 4;226,227,240,239;,
 4;227,228,241,240;,
 4;228,229,242,241;,
 4;229,218,231,242;,
 4;231,230,243,244;,
 4;230,232,245,243;,
 4;232,233,246,245;,
 4;233,234,247,246;,
 4;234,235,248,247;,
 4;235,236,249,248;,
 4;236,237,250,249;,
 4;237,238,251,250;,
 4;238,239,252,251;,
 4;239,240,253,252;,
 4;240,241,254,253;,
 4;241,242,255,254;,
 4;242,231,244,255;;
 
 MeshMaterialList {
  2;
  244;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\MESH\\floor_01.jpg";
   }
  }
 }
 MeshNormals {
  256;
  -0.033562;0.913776;-0.404829;,
  0.228827;0.948322;-0.219824;,
  -0.047663;0.946618;0.318816;,
  -0.316047;0.948119;-0.034409;,
  0.012203;0.999910;-0.005612;,
  -0.020784;0.812510;-0.582577;,
  0.367110;0.796373;-0.480647;,
  0.006680;0.794688;0.606981;,
  -0.418617;0.869406;-0.262474;,
  -0.007810;0.795004;-0.606554;,
  0.385968;0.779063;-0.494055;,
  0.015479;0.771673;0.635831;,
  -0.424289;0.857659;-0.290518;,
  -0.289602;0.893771;0.342498;,
  -0.334878;0.926855;0.169697;,
  -0.355930;0.856168;0.374553;,
  -0.411052;0.907372;0.087815;,
  -0.382956;0.841896;0.380205;,
  -0.428551;0.901001;0.067387;,
  0.207062;0.969728;-0.129432;,
  0.167828;0.962831;0.211639;,
  0.416244;0.896130;-0.153922;,
  0.369832;0.858606;0.354994;,
  0.444696;0.880914;-0.161976;,
  0.413775;0.835702;0.361099;,
  -0.522923;0.774711;-0.355492;,
  -0.318181;0.865014;-0.387957;,
  -0.186849;0.900906;-0.391735;,
  -0.138229;0.880852;-0.452761;,
  0.193288;0.840329;-0.506446;,
  -0.535216;0.777174;-0.330975;,
  -0.257533;0.817240;-0.515554;,
  -0.058622;0.802598;-0.593633;,
  -0.034227;0.774556;-0.631579;,
  0.238275;0.774317;-0.586224;,
  -0.511480;0.811182;-0.283500;,
  -0.210033;0.775183;-0.595800;,
  0.000000;0.677139;-0.735855;,
  -0.000148;0.677260;-0.735744;,
  0.214120;0.714220;-0.666365;,
  -0.522900;0.777016;-0.350460;,
  -0.241215;0.714061;-0.657216;,
  0.007236;0.628028;-0.778157;,
  0.006625;0.630267;-0.776350;,
  0.168597;0.696450;-0.697519;,
  -0.517694;0.724782;-0.454626;,
  -0.267659;0.663763;-0.698411;,
  0.014469;0.668631;-0.743453;,
  0.013538;0.672669;-0.739820;,
  0.144680;0.753610;-0.641201;,
  0.515505;0.697700;-0.497462;,
  0.574735;0.670068;-0.469775;,
  0.599854;0.664992;-0.444928;,
  0.632973;0.650572;-0.419644;,
  0.643670;0.668963;-0.371721;,
  0.498795;0.756482;0.423011;,
  0.164737;0.857021;0.488239;,
  -0.141095;0.890429;0.432699;,
  -0.234717;0.884053;0.404177;,
  -0.342055;0.841591;0.417998;,
  0.551263;0.668332;0.499441;,
  0.176171;0.632605;0.754172;,
  -0.062049;0.635608;0.769515;,
  -0.183414;0.640879;0.745408;,
  -0.290553;0.651775;0.700549;,
  0.622691;0.599608;0.502719;,
  0.165605;0.574725;0.801415;,
  -0.080361;0.536111;0.840314;,
  -0.119669;0.535776;0.835837;,
  -0.208943;0.658655;0.722852;,
  0.676065;0.568456;0.468822;,
  0.197774;0.682635;0.703488;,
  -0.038640;0.723615;0.689122;,
  -0.054052;0.754687;0.653855;,
  -0.199735;0.818645;0.538448;,
  0.689400;0.567556;0.450121;,
  0.255845;0.720568;0.644457;,
  0.033688;0.809981;0.585487;,
  -0.018900;0.869727;0.493171;,
  -0.224985;0.856373;0.464766;,
  -0.512219;0.785928;0.346335;,
  -0.522452;0.729094;0.442116;,
  -0.486768;0.774907;0.403209;,
  -0.509163;0.797830;0.322833;,
  -0.547397;0.762863;0.344087;,
  -0.589789;0.805794;-0.053340;,
  -0.350449;0.935857;-0.036827;,
  -0.259865;0.965571;-0.011909;,
  -0.211177;0.977276;-0.018308;,
  0.164894;0.984623;-0.057682;,
  -0.661457;0.749621;-0.023285;,
  -0.636528;0.771122;0.014290;,
  -0.645533;0.763718;-0.004657;,
  -0.640286;0.767161;-0.038699;,
  0.586789;0.802613;-0.107194;,
  0.721402;0.684092;-0.107692;,
  0.800910;0.596869;-0.047862;,
  0.872345;0.488858;0.005702;,
  0.889044;0.457392;0.019823;,
  0.000000;0.999997;0.002373;,
  0.000000;0.944673;-0.328015;,
  0.152545;0.944618;-0.290563;,
  0.270483;0.944465;-0.186613;,
  0.326853;0.944245;-0.039598;,
  0.308457;0.944006;0.117074;,
  0.219120;0.943804;0.247429;,
  0.079153;0.943687;0.321230;,
  -0.079153;0.943687;0.321230;,
  -0.219120;0.943804;0.247429;,
  -0.308457;0.944006;0.117074;,
  -0.326853;0.944245;-0.039598;,
  -0.270483;0.944465;-0.186613;,
  -0.152545;0.944618;-0.290563;,
  0.000000;0.873031;-0.487665;,
  0.226544;0.873100;-0.431710;,
  0.400922;0.873293;-0.276803;,
  0.483152;0.873565;-0.058731;,
  0.454620;0.873852;0.172349;,
  0.322155;0.874089;0.363572;,
  0.116209;0.874223;0.471413;,
  -0.116209;0.874223;0.471413;,
  -0.322155;0.874089;0.363572;,
  -0.454620;0.873852;0.172349;,
  -0.483152;0.873565;-0.058731;,
  -0.400922;0.873293;-0.276803;,
  -0.226544;0.873100;-0.431710;,
  0.000000;0.824842;-0.565363;,
  0.262667;0.824913;-0.500524;,
  0.464940;0.825108;-0.320978;,
  0.560450;0.825383;-0.068104;,
  0.527504;0.825675;0.200002;,
  0.373891;0.825916;0.421982;,
  0.134889;0.826052;0.547214;,
  -0.134889;0.826052;0.547214;,
  -0.373890;0.825916;0.421981;,
  -0.527504;0.825675;0.200002;,
  -0.560450;0.825383;-0.068105;,
  -0.464940;0.825108;-0.320979;,
  -0.262667;0.824913;-0.500525;,
  0.000793;0.813625;-0.581390;,
  0.271852;0.812053;-0.516398;,
  0.480781;0.811596;-0.331906;,
  0.579603;0.811850;-0.070424;,
  0.545588;0.812120;0.206867;,
  0.386743;0.812343;0.436496;,
  0.139533;0.812469;0.566061;,
  -0.138515;0.813223;0.565227;,
  -0.383968;0.814729;0.434495;,
  -0.541636;0.815141;0.205368;,
  -0.575406;0.814874;-0.069914;,
  -0.477303;0.814622;-0.329506;,
  -0.269633;0.814443;-0.513791;,
  0.001102;0.740650;-0.671890;,
  0.313419;0.740099;-0.594997;,
  0.553151;0.740406;-0.381866;,
  0.666840;0.740783;-0.081023;,
  0.627698;0.741182;0.238001;,
  0.444942;0.741512;0.502182;,
  0.160530;0.741700;0.651239;,
  -0.159463;0.741796;0.651391;,
  -0.443603;0.742253;0.502271;,
  -0.626864;0.741989;0.237685;,
  -0.665954;0.741591;-0.080915;,
  -0.552417;0.741216;-0.381359;,
  -0.312068;0.740949;-0.594649;,
  0.017407;0.714984;-0.698924;,
  0.325923;0.701807;-0.633436;,
  0.581836;0.712451;-0.392277;,
  0.721939;0.687662;-0.076971;,
  0.688153;0.677253;0.260333;,
  0.486208;0.679977;0.548847;,
  0.175540;0.676844;0.714890;,
  -0.179043;0.667425;0.722833;,
  -0.502781;0.653413;0.565918;,
  -0.693664;0.663972;0.279235;,
  -0.707172;0.703512;-0.070555;,
  -0.563772;0.730457;-0.385479;,
  -0.302695;0.745330;-0.594020;,
  0.021209;0.722196;-0.691363;,
  0.314166;0.729057;-0.608091;,
  0.560831;0.739601;-0.372101;,
  0.670375;0.739232;-0.064288;,
  0.628201;0.740540;0.238671;,
  0.446232;0.739749;0.503634;,
  0.161185;0.740843;0.652052;,
  -0.159587;0.742831;0.650180;,
  -0.442680;0.743956;0.500563;,
  -0.620478;0.740627;0.257834;,
  -0.667306;0.742380;-0.059783;,
  -0.558514;0.734291;-0.385848;,
  -0.297882;0.730119;-0.614974;,
  0.004110;0.708388;-0.705811;,
  0.319106;0.729799;-0.604619;,
  0.563563;0.731666;-0.383485;,
  0.650998;0.755582;-0.072781;,
  0.599653;0.766990;0.228346;,
  0.427393;0.764738;0.482193;,
  0.167557;0.792648;0.586202;,
  -0.103424;0.851544;0.513981;,
  -0.354944;0.859997;0.366633;,
  -0.567295;0.799194;0.198660;,
  -0.666901;0.741339;-0.075229;,
  -0.581457;0.705325;-0.405492;,
  -0.326486;0.684215;-0.652117;,
  0.000000;0.797250;-0.603649;,
  0.280178;0.797641;-0.534105;,
  0.495064;0.798721;-0.341988;,
  0.595287;0.800231;-0.072549;,
  0.558826;0.801817;0.211668;,
  0.395233;0.803118;0.445861;,
  0.170199;0.806500;0.566206;,
  -0.107611;0.829737;0.547682;,
  -0.395800;0.830744;0.391417;,
  -0.560859;0.808092;0.180067;,
  -0.595287;0.800231;-0.072549;,
  -0.495064;0.798721;-0.341988;,
  -0.280178;0.797642;-0.534105;,
  0.000000;0.873044;-0.487641;,
  0.226185;0.873400;-0.431293;,
  0.399194;0.874378;-0.275875;,
  0.479223;0.875740;-0.058517;,
  0.449092;0.877165;0.169992;,
  0.317169;0.878330;0.357687;,
  0.129203;0.862789;0.488777;,
  -0.125512;0.837138;0.532397;,
  -0.369997;0.838841;0.399310;,
  -0.473922;0.864079;0.169606;,
  -0.479223;0.875740;-0.058517;,
  -0.399194;0.874378;-0.275875;,
  -0.226185;0.873400;-0.431292;,
  0.000000;0.933735;-0.357965;,
  0.165980;0.933946;-0.316535;,
  0.292760;0.934527;-0.202362;,
  0.351151;0.935335;-0.042918;,
  0.328777;0.936177;0.124411;,
  0.232027;0.936864;0.261629;,
  0.083505;0.937247;0.338519;,
  -0.083505;0.937247;0.338519;,
  -0.232027;0.936864;0.261629;,
  -0.328777;0.936177;0.124411;,
  -0.351152;0.935335;-0.042919;,
  -0.292760;0.934527;-0.202362;,
  -0.165980;0.933946;-0.316535;,
  0.000000;0.972846;-0.231454;,
  0.107281;0.972944;-0.204625;,
  0.189111;0.973212;-0.130749;,
  0.226639;0.973584;-0.027732;,
  0.212012;0.973971;0.080196;,
  0.149515;0.974286;0.168560;,
  0.053787;0.974461;0.218019;,
  -0.053787;0.974461;0.218019;,
  -0.149515;0.974286;0.168560;,
  -0.212012;0.973971;0.080196;,
  -0.226639;0.973584;-0.027732;,
  -0.189111;0.973212;-0.130750;,
  -0.107281;0.972944;-0.204625;;
  244;
  3;0,4,1;,
  3;1,4,2;,
  3;2,4,3;,
  3;3,4,0;,
  4;6,5,0,1;,
  4;5,8,3,0;,
  4;10,9,5,6;,
  4;9,12,8,5;,
  4;13,15,7,2;,
  4;14,13,2,3;,
  4;16,14,3,8;,
  4;16,15,13,14;,
  4;15,17,11,7;,
  4;18,16,8,12;,
  4;18,17,15,16;,
  4;19,21,6,1;,
  4;20,19,1,2;,
  4;22,20,2,7;,
  4;22,21,19,20;,
  4;21,23,10,6;,
  4;24,22,7,11;,
  4;24,23,21,22;,
  4;25,26,31,30;,
  4;26,27,32,31;,
  4;27,28,33,32;,
  4;28,29,34,33;,
  4;29,50,51,34;,
  4;30,31,36,35;,
  4;31,32,37,36;,
  4;32,33,38,37;,
  4;33,34,39,38;,
  4;34,51,52,39;,
  4;35,36,41,40;,
  4;36,37,42,41;,
  4;37,38,43,42;,
  4;38,39,44,43;,
  4;39,52,53,44;,
  4;40,41,46,45;,
  4;41,42,47,46;,
  4;42,43,48,47;,
  4;43,44,49,48;,
  4;44,53,54,49;,
  4;55,56,61,60;,
  4;56,57,62,61;,
  4;57,58,63,62;,
  4;58,59,64,63;,
  4;59,80,81,64;,
  4;60,61,66,65;,
  4;61,62,67,66;,
  4;62,63,68,67;,
  4;63,64,69,68;,
  4;64,81,82,69;,
  4;65,66,71,70;,
  4;66,67,72,71;,
  4;67,68,73,72;,
  4;68,69,74,73;,
  4;69,82,83,74;,
  4;70,71,76,75;,
  4;71,72,77,76;,
  4;72,73,78,77;,
  4;73,74,79,78;,
  4;74,83,84,79;,
  4;95,94,55,60;,
  4;94,95,51,50;,
  4;96,95,60,65;,
  4;95,96,52,51;,
  4;97,96,65,70;,
  4;96,97,53,52;,
  4;98,97,70,75;,
  4;97,98,54,53;,
  4;90,85,25,30;,
  4;85,90,81,80;,
  4;91,90,30,35;,
  4;90,91,82,81;,
  4;92,91,35,40;,
  4;91,92,83,82;,
  4;93,92,40,45;,
  4;92,93,84,83;,
  4;86,85,80,59;,
  4;85,86,26,25;,
  4;87,86,59,58;,
  4;86,87,27,26;,
  4;88,87,58,57;,
  4;87,88,28,27;,
  4;89,88,57,56;,
  4;88,89,29,28;,
  4;94,89,56,55;,
  4;89,94,50,29;,
  3;99,101,100;,
  3;99,102,101;,
  3;99,103,102;,
  3;99,104,103;,
  3;99,105,104;,
  3;99,106,105;,
  3;99,107,106;,
  3;99,108,107;,
  3;99,109,108;,
  3;99,110,109;,
  3;99,111,110;,
  3;99,112,111;,
  3;99,100,112;,
  4;100,101,114,113;,
  4;101,102,115,114;,
  4;102,103,116,115;,
  4;103,104,117,116;,
  4;104,105,118,117;,
  4;105,106,119,118;,
  4;106,107,120,119;,
  4;107,108,121,120;,
  4;108,109,122,121;,
  4;109,110,123,122;,
  4;110,111,124,123;,
  4;111,112,125,124;,
  4;112,100,113,125;,
  4;113,114,127,126;,
  4;114,115,128,127;,
  4;115,116,129,128;,
  4;116,117,130,129;,
  4;117,118,131,130;,
  4;118,119,132,131;,
  4;119,120,133,132;,
  4;120,121,134,133;,
  4;121,122,135,134;,
  4;122,123,136,135;,
  4;123,124,137,136;,
  4;124,125,138,137;,
  4;125,113,126,138;,
  4;126,127,140,139;,
  4;127,128,141,140;,
  4;128,129,142,141;,
  4;129,130,143,142;,
  4;130,131,144,143;,
  4;131,132,145,144;,
  4;132,133,146,145;,
  4;133,134,147,146;,
  4;134,135,148,147;,
  4;135,136,149,148;,
  4;136,137,150,149;,
  4;137,138,151,150;,
  4;138,126,139,151;,
  4;139,140,153,152;,
  4;140,141,154,153;,
  4;141,142,155,154;,
  4;142,143,156,155;,
  4;143,144,157,156;,
  4;144,145,158,157;,
  4;145,146,159,158;,
  4;146,147,160,159;,
  4;147,148,161,160;,
  4;148,149,162,161;,
  4;149,150,163,162;,
  4;150,151,164,163;,
  4;151,139,152,164;,
  4;152,153,166,165;,
  4;153,154,167,166;,
  4;154,155,168,167;,
  4;155,156,169,168;,
  4;156,157,170,169;,
  4;157,158,171,170;,
  4;158,159,172,171;,
  4;159,160,173,172;,
  4;160,161,174,173;,
  4;161,162,175,174;,
  4;162,163,176,175;,
  4;163,164,177,176;,
  4;164,152,165,177;,
  4;165,166,179,178;,
  4;166,167,180,179;,
  4;167,168,181,180;,
  4;168,169,182,181;,
  4;169,170,183,182;,
  4;170,171,184,183;,
  4;171,172,185,184;,
  4;172,173,186,185;,
  4;173,174,187,186;,
  4;174,175,188,187;,
  4;175,176,189,188;,
  4;176,177,190,189;,
  4;177,165,178,190;,
  4;178,179,192,191;,
  4;179,180,193,192;,
  4;180,181,194,193;,
  4;181,182,195,194;,
  4;182,183,196,195;,
  4;183,184,197,196;,
  4;184,185,198,197;,
  4;185,186,199,198;,
  4;186,187,200,199;,
  4;187,188,201,200;,
  4;188,189,202,201;,
  4;189,190,203,202;,
  4;190,178,191,203;,
  4;191,192,205,204;,
  4;192,193,206,205;,
  4;193,194,207,206;,
  4;194,195,208,207;,
  4;195,196,209,208;,
  4;196,197,210,209;,
  4;197,198,211,210;,
  4;198,199,212,211;,
  4;199,200,213,212;,
  4;200,201,214,213;,
  4;201,202,215,214;,
  4;202,203,216,215;,
  4;203,191,204,216;,
  4;204,205,218,217;,
  4;205,206,219,218;,
  4;206,207,220,219;,
  4;207,208,221,220;,
  4;208,209,222,221;,
  4;209,210,223,222;,
  4;210,211,224,223;,
  4;211,212,225,224;,
  4;212,213,226,225;,
  4;213,214,227,226;,
  4;214,215,228,227;,
  4;215,216,229,228;,
  4;216,204,217,229;,
  4;217,218,231,230;,
  4;218,219,232,231;,
  4;219,220,233,232;,
  4;220,221,234,233;,
  4;221,222,235,234;,
  4;222,223,236,235;,
  4;223,224,237,236;,
  4;224,225,238,237;,
  4;225,226,239,238;,
  4;226,227,240,239;,
  4;227,228,241,240;,
  4;228,229,242,241;,
  4;229,217,230,242;,
  4;230,231,244,243;,
  4;231,232,245,244;,
  4;232,233,246,245;,
  4;233,234,247,246;,
  4;234,235,248,247;,
  4;235,236,249,248;,
  4;236,237,250,249;,
  4;237,238,251,250;,
  4;238,239,252,251;,
  4;239,240,253,252;,
  4;240,241,254,253;,
  4;241,242,255,254;,
  4;242,230,243,255;;
 }
 MeshTextureCoords {
  256;
  0.499609;0.230900;,
  0.499568;0.442948;,
  0.684288;0.345840;,
  0.499526;0.660771;,
  0.291975;0.416168;,
  1.934770;0.374131;,
  0.499760;-0.524863;,
  -0.958506;0.443977;,
  2.878980;0.399146;,
  0.499882;-1.129567;,
  -1.924365;0.498518;,
  -0.005782;0.691669;,
  -0.880911;0.831770;,
  0.499375;1.472635;,
  0.234338;0.582466;,
  -1.015739;0.611440;,
  -1.935288;0.760292;,
  0.499253;2.127006;,
  -1.959546;0.635996;,
  0.758821;0.459967;,
  2.009034;0.489032;,
  0.713983;0.556362;,
  1.989697;0.616144;,
  2.952976;0.514821;,
  2.928232;0.593450;,
  -0.364177;0.087870;,
  0.039589;0.076314;,
  0.144212;-0.459833;,
  -0.802913;-0.247830;,
  0.444664;0.068945;,
  0.478511;-0.459769;,
  0.778962;0.065465;,
  0.812809;-0.459705;,
  1.205654;0.062249;,
  1.387994;-0.459594;,
  1.490193;-0.089713;,
  1.719500;-0.065991;,
  0.096561;-0.842855;,
  -1.151266;-0.556022;,
  0.469629;-0.842783;,
  0.842696;-0.842711;,
  1.484587;-0.842588;,
  2.002697;-0.469193;,
  -0.758522;-1.155136;,
  -1.415169;-0.742312;,
  0.469694;-1.154899;,
  0.842761;-1.154828;,
  1.484652;-1.155631;,
  2.228563;-0.856619;,
  -0.883649;-1.467619;,
  -1.489603;-1.103573;,
  0.444293;-1.644873;,
  0.955412;-1.541219;,
  2.074658;-1.693292;,
  2.374793;-1.340700;,
  1.415978;0.959246;,
  1.165214;0.952979;,
  1.146741;1.435624;,
  1.719271;1.121183;,
  0.738522;0.956195;,
  0.833960;1.465717;,
  0.404224;0.959675;,
  0.478146;1.428479;,
  -0.000852;0.967044;,
  0.143864;1.350638;,
  -0.404617;0.978600;,
  -0.803210;1.290729;,
  1.146696;1.690305;,
  2.057883;1.256895;,
  0.812403;1.664440;,
  0.478113;1.622506;,
  0.182127;1.626060;,
  -1.113341;1.456506;,
  1.307880;2.144102;,
  2.230631;1.476372;,
  0.842150;2.013635;,
  0.469091;1.966370;,
  -0.698670;1.934872;,
  -1.193025;1.910514;,
  1.439311;2.598186;,
  2.374176;1.854744;,
  0.842006;2.784209;,
  0.274327;2.913026;,
  -0.829461;2.728040;,
  -1.418665;2.106600;,
  1.955016;0.313230;,
  1.674007;0.285267;,
  2.245765;0.374892;,
  2.489029;0.415857;,
  2.783003;0.439343;,
  -0.750260;0.404688;,
  -0.408895;0.384049;,
  -1.247678;0.396889;,
  -1.513093;0.415367;,
  -2.143228;-0.101100;,
  0.017119;0.372937;,
  0.441508;0.369901;,
  0.788597;0.362678;,
  1.258678;0.359743;,
  0.502019;0.444852;,
  0.558418;0.337335;,
  0.502042;0.323447;,
  0.601873;0.375795;,
  0.622453;0.430017;,
  0.615443;0.487579;,
  0.582449;0.535294;,
  0.531029;0.562231;,
  0.472964;0.562220;,
  0.421555;0.535263;,
  0.388579;0.487535;,
  0.381591;0.429971;,
  0.402192;0.375757;,
  0.445662;0.337314;,
  0.625730;0.213068;,
  0.502070;0.182605;,
  0.721048;0.297430;,
  0.766190;0.416365;,
  0.750813;0.542627;,
  0.678441;0.647289;,
  0.565652;0.706376;,
  0.438286;0.706352;,
  0.325520;0.647221;,
  0.253188;0.542531;,
  0.237861;0.416264;,
  0.283048;0.297346;,
  0.378399;0.213021;,
  0.679291;0.115782;,
  0.502092;0.072130;,
  0.815879;0.236670;,
  0.880565;0.407099;,
  0.858531;0.588026;,
  0.754824;0.738003;,
  0.593203;0.822673;,
  0.410692;0.822638;,
  0.249104;0.737906;,
  0.145455;0.587889;,
  0.123490;0.406953;,
  0.188242;0.236549;,
  0.324877;0.115714;,
  0.730393;0.022614;,
  0.502114;-0.033621;,
  0.906354;0.178349;,
  0.989688;0.397907;,
  0.961302;0.630990;,
  0.827700;0.824201;,
  0.619488;0.933278;,
  0.384366;0.933233;,
  0.176196;0.824076;,
  0.042669;0.630813;,
  0.014373;0.397719;,
  0.097791;0.178194;,
  0.273813;0.022526;,
  0.772673;-0.053876;,
  0.502131;-0.120602;,
  0.981211;0.130692;,
  1.079973;0.390898;,
  1.046332;0.667132;,
  0.887995;0.896114;,
  0.641236;1.025385;,
  0.362584;1.025331;,
  0.115875;0.895885;,
  -0.042373;0.666843;,
  -0.075908;0.390595;,
  0.022954;0.130427;,
  0.231564;-0.054060;,
  0.814784;-0.128746;,
  0.502148;-0.205762;,
  1.055770;0.084539;,
  1.169898;0.385231;,
  1.131022;0.704446;,
  0.948050;0.969054;,
  0.662897;1.118440;,
  0.340889;1.118378;,
  0.055794;0.968883;,
  -0.127076;0.704204;,
  -0.165829;0.384974;,
  -0.051586;0.084326;,
  0.189483;-0.128867;,
  0.869395;-0.180445;,
  0.477401;-0.277011;,
  1.129337;0.044109;,
  1.261405;0.390391;,
  1.217727;0.749040;,
  1.012151;1.046338;,
  0.691771;1.214178;,
  0.329983;1.214108;,
  0.009668;1.046145;,
  -0.195793;0.748768;,
  -0.261954;0.386432;,
  -0.118711;0.009469;,
  0.183549;-0.257839;,
  0.896239;-0.280825;,
  0.500163;-0.378397;,
  1.201542;-0.010617;,
  1.346130;0.370328;,
  1.296878;0.774739;,
  1.065072;1.109970;,
  0.703814;1.299224;,
  0.295865;1.299146;,
  -0.065320;1.109753;,
  -0.296997;0.774432;,
  -0.346092;0.370002;,
  -0.201358;-0.010887;,
  0.104050;-0.280978;,
  0.945685;-0.368337;,
  0.500183;-0.478084;,
  1.289086;-0.064409;,
  1.451716;0.364073;,
  1.396320;0.818949;,
  1.135587;1.196013;,
  0.729248;1.408884;,
  0.246623;1.508874;,
  -0.195583;1.232993;,
  -0.396453;0.818604;,
  -0.451675;0.363706;,
  -0.288879;-0.064713;,
  0.054639;-0.368509;,
  1.067606;-0.588815;,
  0.500233;-0.728583;,
  1.504947;-0.201745;,
  1.712066;0.343952;,
  1.641514;0.923263;,
  1.309456;1.403476;,
  0.791960;1.674580;,
  0.207579;1.674468;,
  -0.309812;1.403165;,
  -0.641685;0.922824;,
  -0.712014;0.343485;,
  -0.504684;-0.202132;,
  -0.067193;-0.589033;,
  1.138241;-0.716511;,
  0.500262;-0.873672;,
  1.630005;-0.281273;,
  1.862899;0.332332;,
  1.783568;0.983735;,
  1.410187;1.523707;,
  0.828292;1.828548;,
  0.171189;1.828422;,
  -0.410588;1.523357;,
  -0.783761;0.983241;,
  -0.862840;0.331807;,
  -0.629709;-0.281708;,
  -0.137777;-0.716758;,
  1.300519;-1.015222;,
  0.500328;-1.212345;,
  1.917320;-0.469320;,
  2.209429;0.300300;,
  2.109928;1.117329;,
  1.641611;1.794595;,
  0.911763;2.176945;,
  0.087585;2.176786;,
  -0.642115;1.794156;,
  -1.110170;1.116709;,
  -1.209356;0.299643;,
  -0.916950;-0.469866;,
  -0.299938;-1.015530;;
 }
}
