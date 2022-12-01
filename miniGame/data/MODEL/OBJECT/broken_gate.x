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
 128;
 -429.90157;355.68431;-116.20662;,
 519.95675;420.57266;-116.20662;,
 471.72686;294.58125;-94.26550;,
 -431.61514;224.77566;-94.26550;,
 519.95675;420.57266;-116.20662;,
 519.95675;420.57266;130.73266;,
 471.72686;294.58125;79.95587;,
 471.72686;294.58125;-94.26550;,
 519.95675;420.57266;130.73266;,
 -429.90157;355.68431;130.73266;,
 -431.61514;224.77566;79.95587;,
 471.72686;294.58125;79.95587;,
 -429.90157;355.68431;130.73266;,
 -429.90157;355.68431;-116.20662;,
 -431.61514;224.77566;-94.26550;,
 -431.61514;224.77566;79.95587;,
 -429.90157;355.68431;130.73266;,
 519.95675;420.57266;130.73266;,
 519.95675;420.57266;-116.20662;,
 -429.90157;355.68431;-116.20662;,
 -431.61514;224.77566;-94.26550;,
 471.72686;294.58125;-94.26550;,
 471.72686;294.58125;79.95587;,
 -431.61514;224.77566;79.95587;,
 -195.63247;-278.73599;-115.09243;,
 -199.73921;-278.73599;-28.65154;,
 -386.25616;-278.73599;-27.54625;,
 -390.05884;-278.73599;-115.09243;,
 -175.04221;-278.73599;61.10530;,
 -410.34512;-278.73599;59.99993;,
 389.00328;-277.69864;-117.73825;,
 421.07462;-277.69864;-27.53264;,
 195.26857;-277.69864;-27.53264;,
 227.34048;-277.69864;-117.73825;,
 398.37750;-277.69864;62.67294;,
 217.96617;-277.69864;62.67294;,
 -346.54429;232.67879;-81.24490;,
 -239.14683;241.62908;-81.24490;,
 -253.62603;123.03130;-66.76565;,
 -332.06509;123.03130;-66.76565;,
 -266.26592;-93.09425;-88.07325;,
 -319.42530;-93.09425;-88.07325;,
 -195.63247;-278.73599;-115.09243;,
 -390.05884;-278.73599;-115.09243;,
 -239.14683;241.62908;-81.24490;,
 -239.14683;241.62908;-27.54625;,
 -253.62603;123.03130;-27.54625;,
 -253.62603;123.03130;-66.76565;,
 -239.14683;241.62908;26.15237;,
 -253.62603;123.03130;11.67316;,
 -232.31875;-93.09425;-27.54625;,
 -266.26592;-93.09425;-88.07325;,
 -232.31875;-93.09425;32.98071;,
 -199.73921;-278.73599;-28.65154;,
 -195.63247;-278.73599;-115.09243;,
 -175.04221;-278.73599;61.10530;,
 -239.14683;241.62908;26.15237;,
 -346.54429;232.67879;26.15237;,
 -332.06509;123.03130;11.67316;,
 -253.62603;123.03130;11.67316;,
 -353.37271;-93.09425;32.98071;,
 -232.31875;-93.09425;32.98071;,
 -410.34512;-278.73599;59.99993;,
 -175.04221;-278.73599;61.10530;,
 -346.54429;232.67879;26.15237;,
 -346.54429;232.67879;-27.54625;,
 -332.06509;123.03130;-27.54625;,
 -332.06509;123.03130;11.67316;,
 -346.54429;232.67879;-81.24490;,
 -332.06509;123.03130;-66.76565;,
 -353.37271;-93.09425;-27.54625;,
 -353.37271;-93.09425;32.98071;,
 -319.42530;-93.09425;-88.07325;,
 -386.25616;-278.73599;-27.54625;,
 -410.34512;-278.73599;59.99993;,
 -390.05884;-278.73599;-115.09243;,
 -346.54429;232.67879;26.15237;,
 -239.14683;241.62908;26.15237;,
 -239.14683;241.62908;-27.54625;,
 -346.54429;232.67879;-27.54625;,
 -239.14683;241.62908;-81.24490;,
 -346.54429;232.67879;-81.24490;,
 255.79580;278.28182;-79.90873;,
 360.54791;287.55811;-79.90873;,
 342.62125;167.40144;-61.98219;,
 273.72237;167.40144;-61.98219;,
 362.67984;-62.09583;-48.35020;,
 253.66353;-62.09583;-48.35020;,
 389.00328;-277.69864;-117.73825;,
 227.34048;-277.69864;-117.73825;,
 360.54791;287.55811;-79.90873;,
 360.54791;287.55811;-27.53264;,
 342.62125;167.40144;-27.53264;,
 342.62125;167.40144;-61.98219;,
 360.54791;287.55811;24.84344;,
 342.62125;167.40144;6.91689;,
 368.09805;-62.09583;-27.53264;,
 362.67984;-62.09583;-48.35020;,
 366.62208;-62.09583;48.29955;,
 421.07462;-277.69864;-27.53264;,
 389.00328;-277.69864;-117.73825;,
 398.37750;-277.69864;62.67294;,
 360.54791;287.55811;24.84344;,
 255.79580;278.28182;24.84344;,
 273.72237;167.40144;6.91689;,
 342.62125;167.40144;6.91689;,
 249.72149;-62.09583;48.29955;,
 366.62208;-62.09583;48.29955;,
 217.96617;-277.69864;62.67294;,
 398.37750;-277.69864;62.67294;,
 255.79580;278.28182;24.84344;,
 255.79580;278.28182;-27.53264;,
 273.72237;167.40144;-27.53264;,
 273.72237;167.40144;6.91689;,
 255.79580;278.28182;-79.90873;,
 273.72237;167.40144;-61.98219;,
 248.24556;-62.09583;-27.53264;,
 249.72149;-62.09583;48.29955;,
 253.66353;-62.09583;-48.35020;,
 195.26857;-277.69864;-27.53264;,
 217.96617;-277.69864;62.67294;,
 227.34048;-277.69864;-117.73825;,
 255.79580;278.28182;24.84344;,
 360.54791;287.55811;24.84344;,
 360.54791;287.55811;-27.53264;,
 255.79580;278.28182;-27.53264;,
 360.54791;287.55811;-79.90873;,
 255.79580;278.28182;-79.90873;;
 
 50;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;25,28,29,26;,
 4;30,31,32,33;,
 4;31,34,35,32;,
 4;36,37,38,39;,
 4;39,38,40,41;,
 4;41,40,42,43;,
 4;44,45,46,47;,
 4;45,48,49,46;,
 4;47,46,50,51;,
 4;46,49,52,50;,
 4;51,50,53,54;,
 4;50,52,55,53;,
 4;56,57,58,59;,
 4;59,58,60,61;,
 4;61,60,62,63;,
 4;64,65,66,67;,
 4;65,68,69,66;,
 4;67,66,70,71;,
 4;66,69,72,70;,
 4;71,70,73,74;,
 4;70,72,75,73;,
 4;76,77,78,79;,
 4;79,78,80,81;,
 4;82,83,84,85;,
 4;85,84,86,87;,
 4;87,86,88,89;,
 4;90,91,92,93;,
 4;91,94,95,92;,
 4;93,92,96,97;,
 4;92,95,98,96;,
 4;97,96,99,100;,
 4;96,98,101,99;,
 4;102,103,104,105;,
 4;105,104,106,107;,
 4;107,106,108,109;,
 4;110,111,112,113;,
 4;111,114,115,112;,
 4;113,112,116,117;,
 4;112,115,118,116;,
 4;117,116,119,120;,
 4;116,118,121,119;,
 4;122,123,124,125;,
 4;125,124,126,127;;
 
 MeshMaterialList {
  7;
  50;
  3,
  4,
  3,
  4,
  2,
  2,
  5,
  5,
  5,
  5,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  6,
  6,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  6,
  6;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/tower_object.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/tower_object.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/tower_object.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/tower_object.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/tower_object.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data/TEXTURE/MESH/tower_object.jpg";
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
  72;
  0.012405;-0.170737;-0.985239;,
  0.933912;-0.357504;-0.000000;,
  0.027038;-0.372055;0.927817;,
  0.000000;-1.000000;-0.000000;,
  -0.999914;0.013089;0.000000;,
  -0.068155;0.997675;0.000000;,
  0.077045;-0.997028;-0.000000;,
  0.005101;-0.126665;-0.991932;,
  0.002567;-0.014367;-0.999894;,
  0.000000;0.121103;-0.992640;,
  0.000000;0.144027;-0.989574;,
  0.992630;-0.121187;-0.000000;,
  0.997663;-0.023999;-0.063981;,
  0.975167;0.162817;-0.150131;,
  0.953168;0.249312;-0.171214;,
  0.999933;-0.011607;-0.000000;,
  0.985585;0.156159;-0.065089;,
  0.968408;0.213004;-0.129676;,
  0.005101;-0.126665;0.991933;,
  -0.991394;-0.130916;0.000000;,
  0.002567;-0.014367;0.999894;,
  -0.997530;-0.028931;-0.064013;,
  -0.001162;0.122898;0.992419;,
  -0.975021;0.163225;-0.150635;,
  -0.002324;0.147607;0.989043;,
  -0.952782;0.250108;-0.172199;,
  0.992630;-0.121187;-0.000000;,
  0.991100;-0.036360;-0.128061;,
  0.957474;0.168290;-0.234355;,
  0.934806;0.284802;-0.212192;,
  -0.991394;-0.130916;0.000000;,
  -0.999864;-0.016510;0.000000;,
  -0.991394;-0.130916;0.000000;,
  -0.990899;-0.041300;-0.128117;,
  -0.985522;0.156556;-0.065089;,
  -0.957160;0.168692;-0.235347;,
  -0.968236;0.213786;-0.129673;,
  -0.934121;0.285587;-0.214146;,
  -0.083050;0.996545;0.000000;,
  -0.083050;0.996545;0.000000;,
  0.006619;-0.154546;-0.987963;,
  0.003313;-0.107044;-0.994249;,
  0.000000;0.125684;-0.992070;,
  0.000000;0.306358;-0.951916;,
  0.989053;-0.147561;-0.000000;,
  0.999318;-0.022336;-0.029420;,
  0.984727;0.159865;-0.068959;,
  0.972982;0.216772;-0.079477;,
  0.999798;-0.019495;0.004877;,
  0.985472;0.154525;0.070473;,
  0.971171;0.199252;0.130860;,
  0.006619;-0.154546;0.987963;,
  -0.987181;-0.159602;0.000000;,
  0.003356;0.011617;0.999927;,
  -0.999162;-0.028437;-0.029442;,
  0.000000;0.122179;0.992508;,
  -0.984727;0.159866;-0.068957;,
  0.000000;0.066518;0.997785;,
  -0.972982;0.216773;-0.079475;,
  0.997650;-0.025155;-0.063728;,
  0.964729;0.162094;-0.207421;,
  0.931443;0.224635;-0.286274;,
  -0.987181;-0.159602;0.000000;,
  -0.999661;-0.025586;0.004881;,
  -0.987181;-0.159602;0.000000;,
  -0.997475;-0.031257;-0.063774;,
  -0.985472;0.154526;0.070474;,
  -0.964730;0.162095;-0.207417;,
  -0.971171;0.199253;0.130862;,
  -0.931444;0.224636;-0.286271;,
  -0.088210;0.996102;0.000000;,
  -0.088210;0.996102;0.000000;;
  50;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;7,7,8,8;,
  4;8,8,9,9;,
  4;9,9,10,10;,
  4;26,11,12,27;,
  4;11,11,15,12;,
  4;27,12,13,28;,
  4;12,15,16,13;,
  4;28,13,14,29;,
  4;13,16,17,14;,
  4;18,18,20,20;,
  4;20,20,22,22;,
  4;22,22,24,24;,
  4;30,19,21,31;,
  4;19,32,33,21;,
  4;31,21,23,34;,
  4;21,33,35,23;,
  4;34,23,25,36;,
  4;23,35,37,25;,
  4;38,38,38,38;,
  4;38,38,39,39;,
  4;40,40,41,41;,
  4;41,41,42,42;,
  4;42,42,43,43;,
  4;44,44,45,59;,
  4;44,44,48,45;,
  4;59,45,46,60;,
  4;45,48,49,46;,
  4;60,46,47,61;,
  4;46,49,50,47;,
  4;51,51,53,53;,
  4;53,53,55,55;,
  4;55,55,57,57;,
  4;62,52,54,63;,
  4;52,64,65,54;,
  4;63,54,56,66;,
  4;54,65,67,56;,
  4;66,56,58,68;,
  4;56,67,69,58;,
  4;70,70,71,71;,
  4;71,71,70,70;;
 }
 MeshTextureCoords {
  128;
  -2.736275;-3.270614;,
  5.010368;-3.093914;,
  4.529999;-1.912526;,
  -2.843019;-2.002039;,
  -0.614591;-4.070837;,
  2.068257;-4.070837;,
  1.502877;-2.701547;,
  -0.389935;-2.701547;,
  5.010368;-3.093914;,
  -2.736275;-3.270614;,
  -2.843019;-2.002039;,
  4.529999;-1.912526;,
  1.798028;-3.365623;,
  -0.884820;-3.365623;,
  -0.646931;-1.942891;,
  1.245881;-1.942891;,
  -2.452886;1.339292;,
  4.071452;1.358400;,
  4.071452;-0.029092;,
  -2.452886;-0.048200;,
  -2.464656;0.036534;,
  3.740173;0.057089;,
  3.740173;1.035997;,
  -2.464656;1.015441;,
  -1.156701;-0.944590;,
  -1.191622;-0.228493;,
  -2.771308;-0.219632;,
  -2.803373;-0.944897;,
  -0.982599;0.515119;,
  -2.975468;0.505590;,
  3.794809;-0.963758;,
  4.066288;-0.216416;,
  2.153849;-0.216773;,
  2.425624;-0.964014;,
  3.873911;0.530839;,
  2.345938;0.530554;,
  -6.030353;-2.393958;,
  -3.683966;-2.539652;,
  -4.000303;-0.609097;,
  -5.714016;-0.609097;,
  -4.276456;2.909032;,
  -5.437866;2.909032;,
  -2.733277;5.930940;,
  -6.981046;5.930940;,
  -0.668250;-3.613863;,
  0.244744;-3.613863;,
  0.257646;-1.594673;,
  -0.409170;-1.594673;,
  1.157739;-3.613863;,
  0.924462;-1.594673;,
  0.238660;2.084979;,
  -0.760183;2.084979;,
  1.267751;2.084979;,
  0.190838;5.245627;,
  -1.282506;5.245627;,
  1.694895;5.245627;,
  -3.683966;-2.539652;,
  -6.030353;-2.393958;,
  -5.714016;-0.609097;,
  -4.000303;-0.609097;,
  -6.179538;2.909032;,
  -3.534788;2.909032;,
  -7.424254;5.930940;,
  -2.283428;5.930940;,
  1.253435;-3.461479;,
  0.340441;-3.461479;,
  0.327539;-1.594673;,
  0.994355;-1.594673;,
  -0.572554;-3.461479;,
  -0.339277;-1.594673;,
  0.346525;2.084979;,
  1.375616;2.084979;,
  -0.712816;2.084979;,
  0.375826;5.245627;,
  1.885767;5.245627;,
  -1.109263;5.245627;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  7.129391;-3.136292;,
  9.417984;-3.287293;,
  9.026327;-1.331362;,
  7.521046;-1.331362;,
  9.464561;2.404434;,
  7.082806;2.404434;,
  10.039668;5.914054;,
  6.507708;5.914054;,
  -1.179889;-4.395828;,
  -0.289380;-4.395828;,
  -0.273407;-2.350098;,
  -0.859125;-2.350098;,
  0.601128;-4.395828;,
  0.312311;-2.350098;,
  -0.296108;1.557214;,
  -0.645224;1.557214;,
  0.994521;1.557214;,
  -0.343313;5.227965;,
  -1.848428;5.227965;,
  1.210604;5.227965;,
  9.417984;-3.287293;,
  7.129391;-3.136292;,
  7.521046;-1.331362;,
  9.026327;-1.331362;,
  6.996682;2.404434;,
  9.550691;2.404434;,
  6.302901;5.914054;,
  10.244473;5.914054;,
  0.694467;-4.237895;,
  -0.196041;-4.237895;,
  -0.212015;-2.350098;,
  0.373703;-2.350098;,
  -1.086550;-4.237895;,
  -0.797733;-2.350098;,
  -0.189314;1.557214;,
  1.098685;1.557214;,
  -0.548086;1.557214;,
  -0.142109;5.227965;,
  1.371359;5.227965;,
  -1.704380;5.227965;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}