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
 85;
 -66.14278;-70.23939;-29.55859;,
 6.72175;-116.37547;-30.10209;,
 7.17297;-63.38637;25.67284;,
 -80.84988;-21.38881;-26.07790;,
 75.70888;-54.95556;-10.05117;,
 82.92717;-10.49991;6.40138;,
 6.72175;56.98211;12.99638;,
 -61.33155;63.02907;10.23040;,
 80.64316;41.66373;11.19629;,
 75.70888;-54.95556;-10.05117;,
 89.13186;-55.31387;-87.25341;,
 110.89184;0.09806;-59.62594;,
 82.92717;-10.49991;6.40138;,
 82.05713;-34.21405;-108.90791;,
 106.99223;24.71383;-91.16426;,
 94.29340;78.75218;-30.66771;,
 80.64316;41.66373;11.19629;,
 94.29340;96.85467;-66.97559;,
 82.05713;-34.21405;-108.90791;,
 82.09563;-63.88251;-128.07334;,
 50.74678;53.87162;-137.40497;,
 106.99223;24.71383;-91.16426;,
 -17.86788;-34.68695;-146.75512;,
 -33.29420;58.93970;-131.21204;,
 6.72175;117.80530;-108.99613;,
 94.29340;96.85467;-66.97559;,
 -31.39717;117.82639;-109.03853;,
 -17.86788;-34.68695;-146.75512;,
 -43.27381;-65.63991;-92.53491;,
 -91.73888;0.27434;-70.25751;,
 -33.29420;58.93970;-131.21204;,
 -66.14278;-70.23939;-29.55859;,
 -80.84988;-21.38881;-26.07790;,
 -80.84988;78.75218;-30.66771;,
 -31.39717;117.82639;-109.03853;,
 -61.33155;63.02907;10.23040;,
 69.70372;-96.41005;-96.89325;,
 -43.27381;-65.63991;-92.53491;,
 89.13186;-55.31387;-87.25341;,
 6.72175;-116.37547;-30.10209;,
 -66.14278;-70.23939;-29.55859;,
 75.70888;-54.95556;-10.05117;,
 -80.84988;78.75218;-30.66771;,
 6.72175;125.65535;-7.28262;,
 94.29340;78.75218;-30.66771;,
 -61.33155;63.02907;10.23040;,
 6.72175;56.98211;12.99638;,
 80.64316;41.66373;11.19629;,
 -86.20481;-61.67689;190.27856;,
 -12.01854;-58.59932;119.37180;,
 -8.65214;-86.84885;196.90169;,
 -83.55432;-20.21127;219.95264;,
 87.78042;-44.24056;170.04727;,
 98.55268;-39.49613;221.18282;,
 19.61165;-4.36935;286.61143;,
 -46.28778;-5.01812;304.84082;,
 107.19822;-18.57934;269.47935;,
 87.78042;-44.24056;170.04727;,
 102.40916;41.54627;111.51004;,
 128.92229;70.34192;142.62261;,
 98.55268;-39.49613;221.18282;,
 90.39622;90.58792;217.77613;,
 107.19822;-18.57934;269.47935;,
 -65.48802;16.32997;141.68993;,
 -86.20481;-61.67689;190.27856;,
 -83.55432;-20.21127;219.95264;,
 -136.65137;23.72739;227.06084;,
 -81.38979;105.89905;283.31226;,
 -70.81975;36.09653;301.90679;,
 -32.12377;127.42332;285.28096;,
 -46.28778;-5.01812;304.84082;,
 -65.48802;16.32997;141.68993;,
 34.73000;-3.93781;60.49393;,
 -12.01854;-58.59932;119.37180;,
 -86.20481;-61.67689;190.27856;,
 102.40916;41.54627;111.51004;,
 87.78042;-44.24056;170.04727;,
 -70.81975;36.09653;301.90679;,
 25.12794;48.75862;334.30035;,
 4.96278;130.82532;277.15284;,
 90.39622;90.58792;217.77613;,
 87.94453;123.40786;241.90342;,
 -46.28778;-5.01812;304.84082;,
 19.61165;-4.36935;286.61143;,
 107.19822;-18.57934;269.47935;;
 
 44;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;9,10,11,12;,
 4;10,13,14,11;,
 4;12,11,15,16;,
 4;11,14,17,15;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;21,20,24,25;,
 4;20,23,26,24;,
 4;27,28,29,30;,
 4;28,31,32,29;,
 4;30,29,33,34;,
 4;29,32,35,33;,
 4;27,19,36,37;,
 4;19,13,38,36;,
 4;37,36,39,40;,
 4;36,38,41,39;,
 4;42,43,24,34;,
 4;43,44,17,24;,
 4;45,46,43,42;,
 4;46,47,44,43;,
 4;48,49,50,51;,
 4;49,52,53,50;,
 4;51,50,54,55;,
 4;50,53,56,54;,
 4;57,58,59,60;,
 4;60,59,61,62;,
 4;63,64,65,66;,
 4;67,66,68,69;,
 4;66,65,70,68;,
 4;71,72,73,74;,
 4;72,75,76,73;,
 4;77,78,79,69;,
 4;78,80,81,79;,
 4;82,83,78,77;,
 4;83,84,80,78;,
 4;66,67,69,79;,
 4;79,81,61,59;,
 3;66,79,59;,
 4;71,66,59,58;,
 3;58,72,71;;
 
 MeshMaterialList {
  1;
  44;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data/TEXTURE/MESH/towerwall.png";
   }
  }
 }
 MeshNormals {
  68;
  -0.507454;-0.457261;0.730345;,
  0.280744;-0.658151;0.698584;,
  -0.635625;-0.217852;0.740623;,
  -0.071990;-0.314525;0.946515;,
  -0.579180;0.151559;0.800987;,
  -0.053558;0.242643;0.968636;,
  0.735162;-0.525618;0.428093;,
  0.935752;-0.352595;-0.006676;,
  0.688173;-0.243923;0.683315;,
  0.992276;-0.095277;0.079437;,
  0.194314;0.266593;0.944018;,
  0.771997;0.479136;0.417671;,
  0.921608;-0.089703;-0.377613;,
  0.731518;0.004267;-0.681809;,
  0.892700;0.146417;-0.426203;,
  0.395001;0.277784;-0.875677;,
  0.774900;0.607976;-0.172901;,
  0.299865;0.448468;-0.841996;,
  -0.325621;-0.334845;-0.884223;,
  -0.600668;-0.606455;-0.520971;,
  -0.454358;0.149327;-0.878214;,
  -0.958288;-0.089408;-0.271461;,
  -0.495657;0.363239;-0.788912;,
  -0.985434;0.158407;-0.061870;,
  -0.275323;-0.806909;-0.522584;,
  0.042983;0.849595;0.525681;,
  0.926179;0.034149;0.375535;,
  -0.673723;-0.669338;-0.313184;,
  -0.880834;-0.420078;-0.218327;,
  -0.150687;-0.741741;-0.653539;,
  0.912431;-0.405387;0.055950;,
  -0.389791;-0.842278;-0.372330;,
  -0.301402;0.836423;0.457769;,
  0.079404;0.992124;0.096871;,
  -0.256091;0.966412;0.021580;,
  -0.317715;-0.901664;0.293358;,
  0.228413;-0.961872;-0.150436;,
  -0.391761;-0.812951;0.430853;,
  -0.015975;-0.954334;0.298316;,
  -0.312907;-0.674367;0.668819;,
  -0.053500;-0.749332;0.660029;,
  0.636136;-0.695393;-0.334304;,
  0.742142;-0.539032;-0.398334;,
  0.519620;-0.853551;0.038019;,
  0.983722;-0.165434;-0.070156;,
  0.061491;-0.846581;0.528696;,
  0.837879;0.107216;0.535222;,
  0.722944;0.207385;0.659048;,
  0.341255;0.376395;0.861319;,
  -0.795416;-0.272250;-0.541473;,
  -0.478759;0.157579;0.863689;,
  -0.873201;-0.479292;0.088311;,
  -0.305113;0.320240;0.896857;,
  -0.380148;-0.109441;0.918428;,
  -0.650653;-0.250814;-0.716759;,
  0.359359;0.082062;0.929584;,
  0.989690;0.065392;0.127427;,
  0.885927;0.052190;0.460878;,
  -0.898706;-0.279490;-0.337954;,
  0.549347;-0.662193;-0.509626;,
  0.673966;0.032615;0.738042;,
  -0.270920;0.754604;-0.597641;,
  -0.239927;0.647802;-0.723040;,
  -0.167726;0.762725;-0.624595;,
  0.071156;0.870287;-0.487379;,
  -0.167207;0.836284;-0.522179;,
  -0.226977;0.862363;-0.452561;,
  -0.213749;0.852699;-0.476671;;
  44;
  4;0,1,3,2;,
  4;1,6,8,3;,
  4;2,3,5,4;,
  4;3,8,10,5;,
  4;6,7,9,8;,
  4;7,12,14,9;,
  4;8,9,11,26;,
  4;9,14,16,11;,
  4;12,13,15,14;,
  4;13,18,20,15;,
  4;14,15,17,16;,
  4;15,20,22,17;,
  4;18,19,21,20;,
  4;19,27,28,21;,
  4;20,21,23,22;,
  4;21,2,4,23;,
  4;18,29,24,19;,
  4;13,12,7,30;,
  4;19,24,31,27;,
  4;30,7,6,1;,
  4;32,25,33,34;,
  4;25,11,16,33;,
  4;4,5,25,32;,
  4;5,10,11,25;,
  4;35,36,38,37;,
  4;36,41,43,38;,
  4;37,38,40,39;,
  4;38,43,45,40;,
  4;41,42,44,43;,
  4;56,44,46,57;,
  4;49,49,58,51;,
  4;50,50,53,52;,
  4;51,37,39,53;,
  4;49,54,54,49;,
  4;59,42,41,36;,
  4;53,55,48,52;,
  4;55,46,47,48;,
  4;39,40,55,53;,
  4;60,57,46,55;,
  4;61,62,62,63;,
  4;63,64,64,65;,
  3;61,63,65;,
  4;66,61,65,66;,
  3;66,67,66;;
 }
 MeshTextureCoords {
  85;
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;;
 }
}
