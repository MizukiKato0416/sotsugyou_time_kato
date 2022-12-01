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
 -754.31012;249.21907;-339.36495;,
 -529.33648;202.79319;-213.55713;,
 -529.33648;84.16983;-339.36495;,
 -943.02169;86.47504;-339.36495;,
 -115.65029;269.18135;-339.36495;,
 -115.65029;154.48693;-528.07691;,
 46.41996;290.22034;-339.36495;,
 298.03580;154.64401;-590.98106;,
 711.72198;269.18135;-339.36495;,
 711.72198;98.53147;-339.36495;,
 -529.33648;-100.84183;-339.36495;,
 -943.02169;-100.84183;-339.36495;,
 -115.65029;-30.36768;-590.98106;,
 298.03580;-30.36768;-653.88507;,
 837.53009;-32.56448;-339.36495;,
 -529.33648;-292.78006;-339.36495;,
 -943.02169;-250.83081;-276.46123;,
 -115.65029;-285.85362;-590.98106;,
 298.03580;-285.85362;-339.36495;,
 523.00987;-295.92698;-465.17300;,
 -529.33648;-399.00718;-339.36495;,
 -880.11886;-340.12872;-213.55713;,
 -115.65029;-353.57662;-339.36495;,
 109.32390;-464.09146;-528.07691;,
 810.88776;184.62255;-217.25743;,
 999.59992;322.66863;30.65828;,
 1188.31203;74.70572;30.65828;,
 999.59992;-88.31554;-280.16131;,
 1125.40783;158.52450;89.86204;,
 1251.21525;84.16983;152.76593;,
 999.59992;170.75785;274.87381;,
 1062.50422;49.17369;337.77771;,
 1188.31203;-100.84183;30.65828;,
 936.69650;-243.77041;-217.25743;,
 1251.21525;-100.84183;215.66988;,
 999.59992;-93.36005;400.68170;,
 1125.40783;-285.85362;30.65828;,
 1062.50422;-298.47449;-152.50331;,
 1125.40783;-285.85362;215.66988;,
 999.59992;-251.36534;337.77718;,
 1062.50422;-454.92535;-32.24571;,
 936.69650;-383.64415;-217.25743;,
 999.59992;-368.08980;152.76593;,
 1062.50422;-306.29773;274.87337;,
 999.59992;170.75785;274.87381;,
 711.72198;200.54461;400.68170;,
 648.81793;67.00772;463.58560;,
 1062.50422;49.17369;337.77771;,
 172.22794;365.73660;400.68170;,
 298.03580;84.16983;589.39351;,
 -52.74630;220.35679;526.48971;,
 -115.65029;84.16983;589.39351;,
 -529.33648;269.18135;337.77771;,
 -529.33648;84.16983;337.77771;,
 -817.21437;186.38246;337.77771;,
 -943.02169;84.16983;400.68170;,
 711.72198;-159.63928;337.77771;,
 999.59992;-93.36005;400.68170;,
 423.84385;-100.84183;526.48971;,
 -466.43233;-126.74021;589.39351;,
 73.06166;16.08441;589.39351;,
 -1005.92648;-91.95949;400.68170;,
 711.72198;-285.85362;400.68170;,
 999.59992;-251.36534;337.77718;,
 298.03580;-285.85362;463.58560;,
 73.06166;-220.65105;652.29737;,
 -529.33648;-285.85362;526.48971;,
 -1005.92648;-276.97127;463.58560;,
 711.72198;-470.86539;274.87381;,
 1062.50422;-306.29773;274.87337;,
 298.03580;-470.86539;274.87381;,
 -115.65029;-479.46568;400.68170;,
 -529.33648;-401.72452;400.68170;,
 -880.11886;-412.99727;337.77771;,
 -817.21437;186.38246;337.77771;,
 -943.02169;228.86109;215.66988;,
 -1068.83058;230.99798;152.76593;,
 -943.02169;84.16983;400.68170;,
 -943.02169;258.46822;-32.24571;,
 -1005.92648;188.19330;-95.14967;,
 -817.21437;276.42205;-280.16131;,
 -1068.83058;84.16983;-154.35341;,
 -754.31012;249.21907;-339.36495;,
 -943.02169;86.47504;-339.36495;,
 -1194.63849;-28.71624;278.57398;,
 -1005.92648;-91.95949;400.68170;,
 -1257.54221;-8.49377;30.65828;,
 -1068.83058;-100.84183;-154.35341;,
 -943.02169;-100.84183;-339.36495;,
 -1131.73459;-226.89561;215.66988;,
 -1005.92648;-276.97127;463.58560;,
 -943.02169;-285.85362;-154.35341;,
 -1194.63849;-285.85362;30.65828;,
 -943.02169;-250.83081;-276.46123;,
 -943.02169;-470.86539;215.66988;,
 -880.11886;-412.99727;337.77771;,
 -943.02169;-434.48819;-91.44941;,
 -943.02169;-470.86539;30.65828;,
 -880.11886;-340.12872;-213.55713;,
 -529.33648;269.18135;337.77771;,
 -529.33648;340.95535;278.57398;,
 -943.02169;228.86109;215.66988;,
 -52.74630;220.35679;526.48971;,
 -115.65029;616.94127;152.76593;,
 172.22794;365.73660;400.68170;,
 298.03580;465.53199;215.66988;,
 711.72198;200.54461;400.68170;,
 711.72198;269.18135;341.47798;,
 1125.40783;158.52450;89.86204;,
 -529.33648;535.90997;30.65828;,
 -943.02169;258.46822;-32.24571;,
 -115.65029;546.53389;30.65828;,
 239.69912;487.58477;28.57764;,
 742.93077;305.58633;28.57764;,
 999.59992;322.66863;30.65828;,
 -592.24039;331.51282;-91.44941;,
 -817.21437;276.42205;-280.16131;,
 -115.65029;400.33931;-154.35341;,
 298.03580;397.86800;-154.35341;,
 648.81793;379.31185;-280.16131;,
 810.88776;184.62255;-217.25743;,
 -529.33648;202.79319;-213.55713;,
 -754.31012;249.21907;-339.36495;,
 -115.65029;269.18135;-339.36495;,
 46.41996;290.22034;-339.36495;,
 711.72198;269.18135;-339.36495;,
 -943.02169;-470.86539;215.66988;,
 -592.24039;-526.90763;278.57398;,
 -529.33648;-401.72452;400.68170;,
 113.89105;-436.03370;217.28951;,
 -115.65029;-479.46568;400.68170;,
 549.65157;-512.47506;215.66988;,
 298.03580;-470.86539;274.87381;,
 648.81793;-523.06690;152.76593;,
 711.72198;-470.86539;274.87381;,
 999.59992;-368.08980;152.76593;,
 -943.02169;-470.86539;30.65828;,
 -529.33648;-470.86539;30.65828;,
 10.15766;-518.72296;30.65828;,
 486.74781;-579.43072;93.56223;,
 711.72198;-563.62154;30.65828;,
 1062.50422;-454.92535;-32.24571;,
 -943.02169;-434.48819;-91.44941;,
 -529.33648;-380.86920;-91.44941;,
 10.15766;-538.46431;-28.54546;,
 235.13179;-543.00719;-217.25743;,
 648.81793;-394.62593;-280.16131;,
 936.69650;-383.64415;-217.25743;,
 -880.11886;-340.12872;-213.55713;,
 -529.33648;-399.00718;-339.36495;,
 -115.65029;-353.57662;-339.36495;,
 109.32390;-464.09146;-528.07691;;
 
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
 4;51,53,59,60;,
 4;53,55,61,59;,
 4;57,56,62,63;,
 4;56,58,64,62;,
 4;58,60,65,64;,
 4;60,59,66,65;,
 4;59,61,67,66;,
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
 4;86,87,91,92;,
 4;87,88,93,91;,
 4;90,89,94,95;,
 4;92,91,96,97;,
 4;91,93,98,96;,
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
 4;27,14,9,24;,
 4;84,86,92,89;,
 4;89,92,136,94;,
 4;58,49,51,60;;
 
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
  110;
  -0.016834;0.673219;-0.739251;,
  -0.013878;0.718062;-0.695841;,
  -0.183059;0.793082;-0.580956;,
  0.035679;0.759493;-0.649536;,
  0.410110;0.578618;-0.704991;,
  -0.335465;0.272448;-0.901796;,
  -0.154448;0.348088;-0.924651;,
  -0.285181;0.555351;-0.781190;,
  0.156629;0.553111;-0.818252;,
  0.546521;0.431289;-0.717847;,
  -0.506292;-0.175384;-0.844339;,
  -0.280735;-0.013323;-0.959693;,
  -0.277544;0.013695;-0.960615;,
  0.154985;-0.077101;-0.984904;,
  0.393735;-0.010436;-0.919165;,
  -0.549908;-0.394711;-0.736074;,
  -0.250998;-0.299546;-0.920474;,
  -0.148093;-0.377367;-0.914146;,
  0.078383;-0.589787;-0.803746;,
  0.156208;-0.579476;-0.799879;,
  -0.414098;-0.682279;-0.602510;,
  -0.119185;-0.796739;-0.592455;,
  -0.170204;-0.795824;-0.581115;,
  -0.004549;-0.687311;-0.726349;,
  0.600283;0.559792;-0.571221;,
  0.544459;0.810704;-0.215227;,
  0.489712;0.820754;0.294184;,
  0.620025;0.105212;-0.777496;,
  0.841219;0.237393;-0.485794;,
  0.699707;0.599953;0.387900;,
  0.591304;-0.187743;-0.784291;,
  0.888561;-0.185839;-0.419433;,
  0.928307;-0.253973;-0.271557;,
  0.723846;-0.117270;-0.679923;,
  0.878069;-0.401380;-0.260555;,
  0.757326;-0.536403;0.372462;,
  0.496778;-0.432088;-0.752669;,
  0.592136;-0.803031;-0.067201;,
  0.544809;-0.749064;0.376943;,
  0.419569;0.679834;0.601488;,
  0.289707;0.633776;0.717216;,
  0.135901;0.628964;0.765464;,
  -0.132954;0.560621;0.817329;,
  -0.211352;0.472616;0.855549;,
  0.436541;0.336365;0.834440;,
  0.285706;0.162764;0.944394;,
  0.187386;0.178258;0.965977;,
  -0.144099;0.259767;0.954859;,
  -0.174777;0.335708;0.925609;,
  0.355468;-0.071089;0.931981;,
  0.237334;-0.079591;0.968162;,
  0.309617;-0.134073;0.941361;,
  0.022684;0.009229;0.999700;,
  -0.179282;0.223697;0.958028;,
  0.409321;-0.377542;0.830613;,
  0.190662;-0.315257;0.929656;,
  0.286400;-0.414944;0.863595;,
  0.108836;-0.443319;0.889732;,
  -0.154539;-0.382017;0.911143;,
  0.470789;-0.697658;0.540028;,
  0.203623;-0.784480;0.585772;,
  0.063275;-0.885565;0.460186;,
  0.001760;-0.908814;0.417197;,
  -0.097135;-0.789560;0.605937;,
  -0.165761;0.586464;0.792833;,
  -0.339272;0.853053;0.396478;,
  -0.438182;0.887519;-0.142503;,
  -0.326303;0.803828;-0.497381;,
  -0.235690;0.482919;0.843350;,
  -0.548672;0.760091;0.348167;,
  -0.666140;0.695034;-0.270528;,
  -0.728795;0.419280;-0.541352;,
  -0.451330;0.212472;0.866693;,
  -0.864345;0.170507;0.473112;,
  -0.941230;0.124273;-0.314073;,
  -0.804589;-0.090359;-0.586917;,
  -0.505334;-0.415451;0.756332;,
  -0.795614;-0.458926;0.395457;,
  -0.821483;-0.529088;-0.212677;,
  -0.734277;-0.443527;-0.513927;,
  -0.324231;-0.740650;0.588482;,
  -0.437791;-0.845281;0.306333;,
  -0.372741;-0.894627;-0.246387;,
  -0.375581;-0.806748;-0.456176;,
  -0.286924;0.832976;0.473103;,
  -0.026430;0.939862;0.340531;,
  0.248815;0.916664;0.312759;,
  0.308847;0.859120;0.408077;,
  -0.275150;0.934664;-0.225158;,
  0.001303;0.919821;-0.392337;,
  0.235897;0.950475;-0.202360;,
  0.326638;0.944915;0.021064;,
  -0.087725;0.797572;-0.596811;,
  -0.084405;0.776761;-0.624115;,
  0.052953;0.879648;-0.472668;,
  0.403271;0.808867;-0.427909;,
  -0.057505;-0.967371;0.246752;,
  -0.066497;-0.978998;0.192720;,
  -0.015603;-0.950228;0.311166;,
  0.249064;-0.885785;0.391601;,
  -0.033960;-0.985100;-0.168598;,
  -0.098957;-0.985632;0.136885;,
  -0.000978;-0.985434;0.170052;,
  0.219833;-0.975534;-0.002614;,
  -0.039198;-0.962969;-0.266749;,
  -0.182039;-0.977275;-0.108606;,
  0.013340;-0.934710;-0.355161;,
  0.190084;-0.761622;-0.619516;,
  0.918932;-0.054628;-0.390614;,
  0.620088;-0.094981;0.778762;;
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
  4;74,75,79,78;,
  4;75,10,15,79;,
  4;76,77,81,80;,
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
  4;27,14,9,24;,
  4;73,74,78,77;,
  4;77,78,82,81;,
  4;51,46,47,52;;
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
  0.800000;0.500000;,
  0.600000;0.500000;,
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
  0.750000;0.750000;,
  0.500000;0.750000;,
  1.000000;0.750000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.750000;1.000000;,
  0.500000;1.000000;,
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
