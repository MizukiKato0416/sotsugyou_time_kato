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
 152;
 -23.46343;24.98358;-9.94377;,
 -17.38343;23.72891;-6.54377;,
 -17.38343;20.52307;-9.94377;,
 -28.56343;20.58537;-9.94377;,
 -6.20343;25.52307;-9.94377;,
 -6.20343;22.42341;-15.04377;,
 -1.82343;26.09165;-9.94377;,
 4.97657;22.42766;-16.74377;,
 16.15657;25.52307;-9.94377;,
 16.15657;20.91120;-9.94377;,
 -17.38343;15.52307;-9.94377;,
 -28.56343;15.52307;-9.94377;,
 -6.20343;17.42766;-16.74377;,
 4.97657;17.42766;-18.44377;,
 19.55657;17.36829;-9.94377;,
 -17.38343;10.33588;-9.94377;,
 -28.56343;11.46957;-8.24377;,
 -6.20343;10.52307;-16.74377;,
 4.97657;10.52307;-9.94377;,
 11.05657;10.25083;-13.34377;,
 -17.38343;7.46506;-9.94377;,
 -26.86343;9.05627;-6.54377;,
 -6.20343;8.69283;-9.94377;,
 -0.12343;5.70613;-15.04377;,
 18.83657;23.23784;-6.64377;,
 23.93657;26.96858;0.05623;,
 29.03657;20.26730;0.05623;,
 23.93657;15.86160;-8.34377;,
 27.33657;22.53253;1.65623;,
 30.73657;20.52307;3.35623;,
 23.93657;22.86314;6.65623;,
 25.63657;19.57729;8.35623;,
 29.03657;15.52307;0.05623;,
 22.23657;11.66038;-6.64377;,
 30.73657;15.52307;5.05623;,
 23.93657;15.72527;10.05623;,
 27.33657;10.52307;0.05623;,
 25.63657;10.18198;-4.89377;,
 27.33657;10.52307;5.05623;,
 23.93657;11.45513;8.35622;,
 25.63657;5.95385;-1.64377;,
 22.23657;7.88025;-6.64377;,
 23.93657;8.30061;3.35623;,
 25.63657;9.97056;6.65622;,
 23.93657;22.86314;6.65623;,
 16.15657;23.66814;10.05623;,
 14.45657;20.05926;11.75623;,
 25.63657;19.57729;8.35623;,
 1.57657;28.13250;10.05623;,
 4.97657;20.52307;16.85623;,
 -4.50343;24.20357;13.45623;,
 -6.20343;20.52307;16.85623;,
 -17.38343;25.52307;8.35623;,
 -17.38343;20.52307;8.35623;,
 -25.16343;23.28540;8.35623;,
 -28.56343;20.52307;10.05623;,
 16.15657;13.93405;8.35623;,
 23.93657;15.72527;10.05623;,
 8.37657;15.52307;13.45623;,
 -1.10343;18.68304;15.15623;,
 -15.68343;14.82316;15.15623;,
 -30.26343;15.76312;10.05623;,
 16.15657;10.52307;10.05623;,
 23.93657;11.45513;8.35622;,
 4.97657;10.52307;11.75623;,
 -1.10343;12.28519;16.85623;,
 -17.38343;10.52307;13.45623;,
 -30.26343;10.76312;11.75623;,
 16.15657;5.52307;6.65623;,
 25.63657;9.97056;6.65622;,
 4.97657;5.52307;6.65623;,
 -6.20343;5.29064;10.05623;,
 -17.38343;7.39162;10.05623;,
 -26.86343;7.08697;8.35623;,
 -25.16343;23.28540;8.35623;,
 -28.56343;24.43340;5.05623;,
 -31.96343;24.49115;3.35623;,
 -28.56343;20.52307;10.05623;,
 -28.56343;25.23354;-1.64377;,
 -30.26343;23.33434;-3.34377;,
 -25.16343;25.71875;-8.34377;,
 -31.96343;20.52307;-4.94377;,
 -23.46343;24.98358;-9.94377;,
 -28.56343;20.58537;-9.94377;,
 -35.36343;17.47229;6.75623;,
 -30.26343;15.76312;10.05623;,
 -37.06343;18.01881;0.05623;,
 -31.96343;15.52307;-4.94377;,
 -28.56343;15.52307;-9.94377;,
 -33.66343;12.11643;5.05623;,
 -30.26343;10.76312;11.75623;,
 -35.36343;10.52307;0.05623;,
 -28.56343;10.52307;-4.94377;,
 -28.56343;11.46957;-8.24377;,
 -28.56343;5.52307;5.05623;,
 -26.86343;7.08697;8.35623;,
 -28.56343;5.52307;0.05623;,
 -28.56343;6.50617;-3.24377;,
 -26.86343;9.05627;-6.54377;,
 -17.38343;25.52307;8.35623;,
 -17.38343;27.46278;6.75623;,
 -28.56343;24.43340;5.05623;,
 -4.50343;24.20357;13.45623;,
 -6.20343;34.92139;3.35623;,
 1.57657;28.13250;10.05623;,
 4.97657;30.82950;5.05623;,
 16.15657;23.66814;10.05623;,
 16.15657;25.52307;8.45623;,
 27.33657;22.53253;1.65623;,
 -17.38343;32.73150;0.05623;,
 -28.56343;25.23354;-1.64377;,
 -6.20343;33.01861;0.05623;,
 3.40000;31.42549;0.00000;,
 17.00000;26.50692;0.00000;,
 23.93657;26.96858;0.05623;,
 -19.08343;27.20761;-3.24377;,
 -25.16343;25.71875;-8.34377;,
 -6.20343;29.06766;-4.94377;,
 4.97657;29.00087;-4.94377;,
 14.45657;28.49937;-8.34377;,
 18.83657;23.23784;-6.64377;,
 -17.38343;23.72891;-6.54377;,
 -23.46343;24.98358;-9.94377;,
 -6.20343;25.52307;-9.94377;,
 -1.82343;26.09165;-9.94377;,
 16.15657;25.52307;-9.94377;,
 -28.56343;5.52307;5.05623;,
 -19.08343;4.00851;6.75623;,
 -17.38343;7.39162;10.05623;,
 0.00000;6.46441;5.10000;,
 -6.20343;5.29064;10.05623;,
 11.77657;4.39855;5.05623;,
 4.97657;5.52307;6.65623;,
 14.45657;4.11230;3.35623;,
 16.15657;5.52307;6.65623;,
 23.93657;8.30061;3.35623;,
 -28.56343;5.52307;0.05623;,
 -17.38343;5.52307;0.05623;,
 -2.80343;4.22970;0.05623;,
 10.07657;2.58905;1.75623;,
 16.15657;3.01630;0.05623;,
 25.63657;5.95385;-1.64377;,
 -28.56343;6.50617;-3.24377;,
 -17.38343;7.95524;-3.24377;,
 -2.80343;3.69618;-1.54377;,
 3.27657;3.57341;-6.64377;,
 14.45657;7.58346;-8.34377;,
 22.23657;7.88025;-6.64377;,
 -26.86343;9.05627;-6.54377;,
 -17.38343;7.46506;-9.94377;,
 -6.20343;8.69283;-9.94377;,
 -0.12343;5.70613;-15.04377;;
 
 107;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;3,2,10,11;,
 4;2,5,12,10;,
 4;5,7,13,12;,
 4;7,9,14,13;,
 4;11,10,15,16;,
 4;10,12,17,15;,
 4;12,13,18,17;,
 4;13,14,19,18;,
 4;16,15,20,21;,
 4;15,17,22,20;,
 4;17,18,23,22;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;28,30,31,29;,
 4;27,26,32,33;,
 4;26,29,34,32;,
 4;29,31,35,34;,
 4;33,32,36,37;,
 4;32,34,38,36;,
 4;34,35,39,38;,
 4;37,36,40,41;,
 4;36,38,42,40;,
 4;38,39,43,42;,
 4;44,45,46,47;,
 4;45,48,49,46;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 4;47,46,56,57;,
 4;46,49,58,56;,
 4;49,51,59,58;,
 4;51,53,60,59;,
 4;53,55,61,60;,
 4;57,56,62,63;,
 4;56,58,64,62;,
 4;58,59,65,64;,
 4;59,60,66,65;,
 4;60,61,67,66;,
 4;63,62,68,69;,
 4;62,64,70,68;,
 4;64,65,71,70;,
 4;65,66,72,71;,
 4;66,67,73,72;,
 4;74,75,76,77;,
 4;75,78,79,76;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;77,76,84,85;,
 4;76,79,86,84;,
 4;79,81,87,86;,
 4;81,83,88,87;,
 4;85,84,89,90;,
 4;84,86,91,89;,
 4;86,87,92,91;,
 4;87,88,93,92;,
 4;90,89,94,95;,
 4;89,91,96,94;,
 4;91,92,97,96;,
 4;92,93,98,97;,
 4;74,99,100,101;,
 4;99,102,103,100;,
 4;102,104,105,103;,
 4;104,106,107,105;,
 4;106,30,108,107;,
 4;101,100,109,110;,
 4;100,103,111,109;,
 4;103,105,112,111;,
 4;105,107,113,112;,
 4;107,108,114,113;,
 4;110,109,115,116;,
 4;109,111,117,115;,
 4;111,112,118,117;,
 4;112,113,119,118;,
 4;113,114,120,119;,
 4;116,115,121,122;,
 4;115,117,123,121;,
 4;117,118,124,123;,
 4;118,119,125,124;,
 4;126,127,128,95;,
 4;127,129,130,128;,
 4;129,131,132,130;,
 4;131,133,134,132;,
 4;133,135,43,134;,
 4;136,137,127,126;,
 4;137,138,129,127;,
 4;138,139,131,129;,
 4;139,140,133,131;,
 4;140,141,135,133;,
 4;142,143,137,136;,
 4;143,144,138,137;,
 4;144,145,139,138;,
 4;145,146,140,139;,
 4;146,147,141,140;,
 4;148,149,143,142;,
 4;149,150,144,143;,
 4;150,151,145,144;,
 4;146,145,151,18;,
 4;27,33,19,14;,
 3;147,33,37;,
 3;146,18,19;,
 4;33,147,146,19;,
 4;24,9,125,119;,
 4;27,14,9,24;;
 
 MeshMaterialList {
  1;
  107;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  }
 }
 MeshNormals {
  113;
  -0.016835;0.673220;-0.739251;,
  -0.013878;0.718061;-0.695841;,
  -0.183059;0.793082;-0.580956;,
  0.035679;0.759493;-0.649536;,
  0.410109;0.578618;-0.704991;,
  -0.335466;0.272449;-0.901795;,
  -0.154448;0.348088;-0.924652;,
  -0.285180;0.555351;-0.781190;,
  0.156630;0.553111;-0.818252;,
  0.546521;0.431289;-0.717847;,
  -0.506293;-0.175384;-0.844339;,
  -0.280734;-0.013323;-0.959693;,
  -0.277544;0.013694;-0.960615;,
  0.154985;-0.077101;-0.984904;,
  0.393735;-0.010436;-0.919165;,
  -0.549907;-0.394712;-0.736074;,
  -0.250998;-0.299547;-0.920474;,
  -0.148093;-0.377367;-0.914146;,
  0.078383;-0.589787;-0.803746;,
  0.156208;-0.579476;-0.799879;,
  -0.414095;-0.682280;-0.602511;,
  -0.119186;-0.796738;-0.592455;,
  -0.170204;-0.795824;-0.581115;,
  -0.004549;-0.687310;-0.726350;,
  0.600283;0.559792;-0.571221;,
  0.544459;0.810704;-0.215228;,
  0.489713;0.820754;0.294183;,
  0.620025;0.105211;-0.777496;,
  0.841218;0.237392;-0.485796;,
  0.699707;0.599954;0.387900;,
  0.591304;-0.187743;-0.784291;,
  0.888560;-0.185839;-0.419434;,
  0.928306;-0.253974;-0.271559;,
  0.723845;-0.117271;-0.679923;,
  0.878069;-0.401380;-0.260556;,
  0.757325;-0.536405;0.372462;,
  0.496778;-0.432089;-0.752670;,
  0.592135;-0.803032;-0.067201;,
  0.544808;-0.749065;0.376943;,
  0.419569;0.679833;0.601489;,
  0.299002;0.645499;0.702801;,
  0.133946;0.682176;0.718814;,
  -0.148407;0.630846;0.761583;,
  -0.215759;0.503648;0.836533;,
  0.436541;0.336365;0.834440;,
  0.316325;0.156317;0.935683;,
  0.265325;0.352862;0.897269;,
  -0.233946;0.403837;0.884412;,
  -0.184874;0.302222;0.935138;,
  0.355468;-0.071089;0.931981;,
  0.252561;-0.103246;0.962057;,
  0.316321;-0.292253;0.902513;,
  0.002045;-0.196247;0.980552;,
  -0.181950;0.154378;0.971114;,
  0.409320;-0.377543;0.830613;,
  0.190662;-0.315258;0.929656;,
  0.286401;-0.414944;0.863595;,
  0.108836;-0.443319;0.889732;,
  -0.154539;-0.382017;0.911143;,
  0.470788;-0.697659;0.540028;,
  0.203624;-0.784480;0.585772;,
  0.063275;-0.885565;0.460187;,
  0.001760;-0.908814;0.417197;,
  -0.097135;-0.789560;0.605937;,
  -0.165761;0.586464;0.792833;,
  -0.339272;0.853053;0.396478;,
  -0.438183;0.887518;-0.142504;,
  -0.326304;0.803827;-0.497380;,
  -0.235690;0.482918;0.843351;,
  -0.548673;0.760090;0.348167;,
  -0.666141;0.695033;-0.270529;,
  -0.728796;0.419279;-0.541351;,
  -0.451330;0.212472;0.866693;,
  -0.864345;0.170507;0.473112;,
  -0.824442;0.262010;-0.501644;,
  -0.804590;-0.090358;-0.586916;,
  -0.505334;-0.415451;0.756332;,
  -0.795614;-0.458925;0.395457;,
  -0.815616;-0.578508;-0.009925;,
  -0.734277;-0.443527;-0.513927;,
  -0.324231;-0.740649;0.588483;,
  -0.437792;-0.845280;0.306334;,
  -0.372742;-0.894627;-0.246387;,
  -0.375579;-0.806749;-0.456177;,
  -0.286923;0.832976;0.473103;,
  -0.026430;0.939862;0.340531;,
  0.248815;0.916664;0.312760;,
  0.308846;0.859120;0.408077;,
  -0.275150;0.934664;-0.225158;,
  0.001303;0.919821;-0.392336;,
  0.235897;0.950475;-0.202359;,
  0.326638;0.944915;0.021065;,
  -0.087725;0.797572;-0.596811;,
  -0.084404;0.776761;-0.624114;,
  0.052953;0.879648;-0.472668;,
  0.403270;0.808868;-0.427909;,
  -0.057505;-0.967371;0.246752;,
  -0.066497;-0.978998;0.192720;,
  -0.015603;-0.950227;0.311166;,
  0.249065;-0.885785;0.391602;,
  -0.033960;-0.985100;-0.168597;,
  -0.098957;-0.985632;0.136886;,
  -0.000977;-0.985434;0.170053;,
  0.219834;-0.975534;-0.002614;,
  -0.039198;-0.962969;-0.266748;,
  -0.182040;-0.977275;-0.108605;,
  0.013340;-0.934710;-0.355161;,
  0.190084;-0.761622;-0.619516;,
  0.918931;-0.054629;-0.390618;,
  0.620087;-0.094981;0.778763;,
  -0.024842;-0.632876;0.773854;,
  -0.914771;-0.281483;0.289761;,
  -0.646780;-0.272517;-0.712327;;
  107;
  4;0,1,6,5;,
  4;1,2,7,6;,
  4;2,3,8,7;,
  4;3,4,9,8;,
  4;5,6,11,10;,
  4;6,7,12,11;,
  4;7,8,13,12;,
  4;8,9,14,13;,
  4;10,11,16,15;,
  4;11,12,17,16;,
  4;12,13,18,17;,
  4;13,14,19,18;,
  4;15,16,21,20;,
  4;16,17,22,21;,
  4;17,18,23,22;,
  4;24,25,28,27;,
  4;25,26,29,28;,
  4;26,39,44,29;,
  4;27,28,31,30;,
  4;28,108,32,31;,
  4;29,44,49,109;,
  4;30,31,34,33;,
  4;31,32,35,34;,
  4;109,49,54,35;,
  4;33,34,37,36;,
  4;34,35,38,37;,
  4;35,54,59,38;,
  4;39,40,45,44;,
  4;40,41,46,45;,
  4;41,42,47,46;,
  4;42,43,48,47;,
  4;43,64,68,48;,
  4;44,45,50,49;,
  4;45,46,51,50;,
  4;110,110,52,51;,
  4;47,48,53,52;,
  4;48,68,72,53;,
  4;49,50,55,54;,
  4;50,51,56,55;,
  4;51,52,57,56;,
  4;52,53,58,57;,
  4;53,72,76,58;,
  4;54,55,60,59;,
  4;55,56,61,60;,
  4;56,57,62,61;,
  4;57,58,63,62;,
  4;58,76,80,63;,
  4;64,65,69,68;,
  4;65,66,70,69;,
  4;66,67,71,70;,
  4;67,0,5,71;,
  4;68,69,73,72;,
  4;69,70,74,73;,
  4;70,71,75,74;,
  4;71,5,10,75;,
  4;72,73,77,76;,
  4;73,111,78,77;,
  4;74,75,79,112;,
  4;75,10,15,79;,
  4;76,77,81,80;,
  4;77,78,82,81;,
  4;78,79,83,82;,
  4;79,15,20,83;,
  4;64,43,84,65;,
  4;43,42,85,84;,
  4;42,41,86,85;,
  4;41,40,87,86;,
  4;40,39,26,87;,
  4;65,84,88,66;,
  4;84,85,89,88;,
  4;85,86,90,89;,
  4;86,87,91,90;,
  4;87,26,25,91;,
  4;66,88,92,67;,
  4;88,89,93,92;,
  4;89,90,94,93;,
  4;90,91,95,94;,
  4;91,25,24,95;,
  4;67,92,1,0;,
  4;92,93,2,1;,
  4;93,94,3,2;,
  4;94,95,4,3;,
  4;81,96,63,80;,
  4;96,97,62,63;,
  4;97,98,61,62;,
  4;98,99,60,61;,
  4;99,38,59,60;,
  4;82,100,96,81;,
  4;100,101,97,96;,
  4;101,102,98,97;,
  4;102,103,99,98;,
  4;103,37,38,99;,
  4;83,104,100,82;,
  4;104,105,101,100;,
  4;105,106,102,101;,
  4;106,107,103,102;,
  4;107,36,37,103;,
  4;20,21,104,83;,
  4;21,22,105,104;,
  4;22,23,106,105;,
  4;107,106,23,18;,
  4;27,30,19,14;,
  3;36,30,33;,
  3;107,18,19;,
  4;30,36,107,19;,
  4;24,9,4,95;,
  4;27,14,9,24;;
 }
 MeshTextureCoords {
  152;
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;0.250000;,
  0.000000;0.250000;,
  0.400000;0.000000;,
  0.400000;0.250000;,
  0.600000;0.000000;,
  0.600000;0.250000;,
  0.800000;0.000000;,
  0.800000;0.250000;,
  0.200000;0.500000;,
  0.000000;0.500000;,
  0.400000;0.500000;,
  0.600000;0.500000;,
  0.800000;0.500000;,
  0.200000;0.750000;,
  0.000000;0.750000;,
  0.400000;0.750000;,
  0.600000;0.750000;,
  0.800000;0.750000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;1.000000;,
  0.600000;1.000000;,
  0.250000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.250000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.500000;0.500000;,
  0.250000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.750000;,
  0.250000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.500000;1.000000;,
  0.250000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.200000;0.250000;,
  0.000000;0.250000;,
  0.400000;0.000000;,
  0.400000;0.250000;,
  0.600000;0.000000;,
  0.600000;0.250000;,
  0.800000;0.000000;,
  0.800000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.200000;0.500000;,
  0.000000;0.500000;,
  0.400000;0.500000;,
  0.600000;0.500000;,
  0.800000;0.500000;,
  1.000000;0.500000;,
  0.200000;0.750000;,
  0.000000;0.750000;,
  0.400000;0.750000;,
  0.600000;0.750000;,
  0.800000;0.750000;,
  1.000000;0.750000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.500000;0.750000;,
  0.750000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.200000;0.000000;,
  0.200000;0.250000;,
  0.000000;0.250000;,
  0.400000;0.000000;,
  0.400000;0.250000;,
  0.600000;0.000000;,
  0.600000;0.250000;,
  0.800000;0.000000;,
  0.800000;0.250000;,
  1.000000;0.250000;,
  0.200000;0.500000;,
  0.000000;0.500000;,
  0.400000;0.500000;,
  0.600000;0.500000;,
  0.800000;0.500000;,
  1.000000;0.500000;,
  0.200000;0.750000;,
  0.000000;0.750000;,
  0.400000;0.750000;,
  0.600000;0.750000;,
  0.800000;0.750000;,
  1.000000;0.750000;,
  0.200000;1.000000;,
  0.000000;1.000000;,
  0.400000;1.000000;,
  0.600000;1.000000;,
  0.800000;1.000000;,
  0.000000;0.750000;,
  0.200000;0.750000;,
  0.200000;1.000000;,
  0.400000;0.750000;,
  0.400000;1.000000;,
  0.600000;0.750000;,
  0.600000;1.000000;,
  0.800000;0.750000;,
  0.800000;1.000000;,
  1.000000;0.750000;,
  0.000000;0.500000;,
  0.200000;0.500000;,
  0.400000;0.500000;,
  0.600000;0.500000;,
  0.800000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.250000;,
  0.200000;0.250000;,
  0.400000;0.250000;,
  0.600000;0.250000;,
  0.800000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.000000;,
  0.200000;0.000000;,
  0.400000;0.000000;,
  0.600000;0.000000;;
 }
}
