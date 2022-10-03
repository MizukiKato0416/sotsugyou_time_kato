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
 340;
 -18.91292;13.18534;19.64346;,
 -18.89363;5.53186;19.59487;,
 -18.92030;5.58618;11.02866;,
 -18.93961;13.23965;11.07725;,
 -24.29190;0.10630;19.57729;,
 -24.31859;0.16060;11.01108;,
 -31.94550;0.08686;19.60101;,
 -31.97218;0.14117;11.03480;,
 -37.37106;5.48493;19.65213;,
 -37.39774;5.53924;11.08592;,
 -37.39035;13.13840;19.70072;,
 -37.41703;13.19272;11.13451;,
 -31.99206;18.56397;19.71830;,
 -32.01875;18.61828;11.15209;,
 -24.33847;18.58342;19.69458;,
 -24.36513;18.63773;11.12837;,
 -28.14198;9.33514;19.64780;,
 -18.89363;5.53186;19.59487;,
 -18.91292;13.18534;19.64346;,
 -28.14198;9.33514;19.64780;,
 -24.29190;0.10630;19.57729;,
 -28.14198;9.33514;19.64780;,
 -31.94550;0.08686;19.60101;,
 -28.14198;9.33514;19.64780;,
 -37.37106;5.48493;19.65213;,
 -28.14198;9.33514;19.64780;,
 -37.39035;13.13840;19.70072;,
 -28.14198;9.33514;19.64780;,
 -31.99206;18.56397;19.71830;,
 -28.14198;9.33514;19.64780;,
 -24.33847;18.58342;19.69458;,
 -28.14198;9.33514;19.64780;,
 -18.91292;13.18534;19.64346;,
 -28.16867;9.38945;11.08159;,
 -18.93961;13.23965;11.07725;,
 -18.92030;5.58618;11.02866;,
 -28.16867;9.38945;11.08159;,
 -24.31859;0.16060;11.01108;,
 -28.16867;9.38945;11.08159;,
 -31.97218;0.14117;11.03480;,
 -28.16867;9.38945;11.08159;,
 -37.39774;5.53924;11.08592;,
 -28.16867;9.38945;11.08159;,
 -37.41703;13.19272;11.13451;,
 -28.16867;9.38945;11.08159;,
 -32.01875;18.61828;11.15209;,
 -28.16867;9.38945;11.08159;,
 -24.36513;18.63773;11.12837;,
 -28.16867;9.38945;11.08159;,
 -18.93961;13.23965;11.07725;,
 -18.91292;13.18534;-11.33250;,
 -18.89363;5.53186;-11.38109;,
 -18.92030;5.58618;-19.94730;,
 -18.93961;13.23965;-19.89871;,
 -24.29190;0.10630;-11.39867;,
 -24.31859;0.16060;-19.96488;,
 -31.94550;0.08686;-11.37495;,
 -31.97218;0.14117;-19.94116;,
 -37.37106;5.48493;-11.32383;,
 -37.39774;5.53924;-19.89004;,
 -37.39035;13.13840;-11.27524;,
 -37.41703;13.19272;-19.84146;,
 -31.99206;18.56397;-11.25766;,
 -32.01875;18.61828;-19.82387;,
 -24.33847;18.58342;-11.28139;,
 -24.36513;18.63773;-19.84760;,
 -18.91292;13.18534;-11.33250;,
 -18.93961;13.23965;-19.89871;,
 -28.14198;9.33514;-11.32816;,
 -28.14198;9.33514;-11.32816;,
 -28.14198;9.33514;-11.32816;,
 -28.14198;9.33514;-11.32816;,
 -28.14198;9.33514;-11.32816;,
 -28.14198;9.33514;-11.32816;,
 -28.14198;9.33514;-11.32816;,
 -28.14198;9.33514;-11.32816;,
 -28.16867;9.38945;-19.89437;,
 -28.16867;9.38945;-19.89437;,
 -28.16867;9.38945;-19.89437;,
 -28.16867;9.38945;-19.89437;,
 -28.16867;9.38945;-19.89437;,
 -28.16867;9.38945;-19.89437;,
 -28.16867;9.38945;-19.89437;,
 -28.16867;9.38945;-19.89437;,
 31.38188;10.32731;-11.38980;,
 31.39698;4.33324;-11.44217;,
 31.37610;4.37578;-20.67381;,
 31.36097;10.36985;-20.62145;,
 27.16068;-0.01232;-11.47285;,
 27.14825;0.12657;-20.69275;,
 21.16653;-0.02753;-11.44730;,
 21.15411;0.11135;-20.66719;,
 16.92581;4.29649;-11.38045;,
 16.90492;4.33902;-20.61210;,
 16.91069;10.29055;-11.32810;,
 16.88980;10.33308;-20.55974;,
 21.13854;14.53976;-11.30914;,
 21.11764;14.58228;-20.54079;,
 27.13269;14.55498;-11.33471;,
 27.11180;14.59752;-20.56636;,
 31.38188;10.32731;-11.38980;,
 31.36097;10.36985;-20.62145;,
 24.14537;7.21555;-11.39687;,
 24.14537;7.21555;-11.39687;,
 24.14537;7.21555;-11.39687;,
 24.14537;7.21555;-11.39687;,
 24.14537;7.21555;-11.39687;,
 24.14537;7.21555;-11.39687;,
 24.14537;7.21555;-11.39687;,
 24.14537;7.21555;-11.39687;,
 24.13295;7.35443;-20.61679;,
 24.13295;7.35443;-20.61679;,
 24.13295;7.35443;-20.61679;,
 24.13295;7.35443;-20.61679;,
 24.13295;7.35443;-20.61679;,
 24.13295;7.35443;-20.61679;,
 24.13295;7.35443;-20.61679;,
 24.13295;7.35443;-20.61679;,
 31.32856;10.32731;20.31954;,
 31.34368;4.33324;20.26717;,
 31.32280;4.37578;11.03553;,
 31.30766;10.36985;11.08789;,
 27.11584;0.08404;20.24823;,
 27.09494;0.12657;11.01659;,
 16.87250;4.29649;20.32890;,
 16.85738;10.29055;20.38125;,
 16.83650;10.33308;11.14960;,
 16.85160;4.33902;11.09724;,
 21.08523;14.53976;20.40019;,
 21.06432;14.58228;11.16855;,
 27.07937;14.55498;20.37463;,
 27.05849;14.59752;11.14298;,
 31.32856;10.32731;20.31954;,
 31.30766;10.36985;11.08789;,
 24.10054;7.31190;20.32423;,
 24.10054;7.31190;20.32423;,
 24.10054;7.31190;20.32423;,
 21.12169;0.06882;20.27380;,
 24.10054;7.31190;20.32423;,
 24.10054;7.31190;20.32423;,
 24.10054;7.31190;20.32423;,
 24.10054;7.31190;20.32423;,
 24.10054;7.31190;20.32423;,
 24.07964;7.35443;11.09258;,
 24.07964;7.35443;11.09258;,
 24.07964;7.35443;11.09258;,
 21.10080;0.11135;11.04216;,
 24.07964;7.35443;11.09258;,
 24.07964;7.35443;11.09258;,
 24.07964;7.35443;11.09258;,
 24.07964;7.35443;11.09258;,
 24.07964;7.35443;11.09258;,
 47.90027;6.98522;-10.46171;,
 47.90027;6.98522;9.53829;,
 47.90027;2.81930;9.53829;,
 47.90027;2.81930;-10.46171;,
 34.94094;10.65830;9.53829;,
 34.94094;10.65830;-10.46171;,
 34.94094;2.81930;-10.46171;,
 34.94094;2.81930;9.53829;,
 47.90027;6.98522;-10.46171;,
 34.94094;10.65830;-10.46171;,
 34.94094;2.81930;-10.46171;,
 47.90027;2.81930;-10.46171;,
 30.72761;9.94155;-23.46911;,
 41.31911;6.20547;-23.46911;,
 41.31911;2.89913;-23.46911;,
 30.72761;2.89913;-23.46911;,
 41.31911;6.20547;-23.46911;,
 47.92857;7.00791;-10.45827;,
 47.92857;2.88121;-10.45827;,
 41.31911;2.89913;-23.46911;,
 34.91969;10.62430;-10.45827;,
 30.72761;9.94155;-23.46911;,
 30.72761;2.89913;-23.46911;,
 34.91969;2.88121;-10.45827;,
 41.31911;6.20547;-23.46911;,
 30.72761;9.94155;-23.46911;,
 30.72761;2.89913;-23.46911;,
 41.31911;2.89913;-23.46911;,
 47.91329;6.98416;9.61756;,
 40.38391;6.98416;23.21124;,
 40.38391;2.80517;23.21124;,
 47.91329;2.80517;9.61756;,
 40.38391;6.98416;23.21124;,
 30.91918;10.67792;23.21124;,
 30.91918;2.80517;23.21124;,
 40.38391;2.80517;23.21124;,
 30.91918;10.67792;23.21124;,
 34.95815;10.67792;9.61756;,
 34.95815;2.80517;9.61756;,
 30.91918;2.80517;23.21124;,
 47.91329;6.98416;9.61756;,
 34.95815;10.67792;9.61756;,
 34.95815;2.80517;9.61756;,
 47.91329;2.80517;9.61756;,
 -29.33757;10.18029;-11.15192;,
 35.13226;7.84181;-11.15192;,
 35.13226;4.86608;-11.15192;,
 -29.33757;7.20456;-11.15192;,
 35.13226;7.84181;10.72664;,
 -29.33757;10.18029;10.72664;,
 -29.33757;7.20456;10.72664;,
 35.13226;4.86608;10.72664;,
 -29.33757;10.18029;10.72664;,
 -29.33757;10.18029;-11.15192;,
 -29.33757;7.20456;-11.15192;,
 -29.33757;7.20456;10.72664;,
 35.13226;7.84181;10.72664;,
 35.13226;7.84181;-11.15192;,
 -29.33757;10.18029;-11.15192;,
 -29.33757;7.20456;-11.15192;,
 35.13226;4.86608;-11.15192;,
 35.13226;4.86608;10.72664;,
 -18.45900;24.71332;10.34100;,
 -27.11925;25.65752;5.34100;,
 -27.11925;10.14520;5.34100;,
 -18.45900;9.72106;10.34100;,
 -25.38720;25.65752;4.34100;,
 -18.45900;24.71332;8.34100;,
 -18.45900;9.72106;8.34100;,
 -25.38720;10.14520;4.34100;,
 -27.11925;25.65752;-4.65900;,
 -27.11925;10.14520;-4.65900;,
 -25.38720;25.65752;-3.65900;,
 -25.38720;10.14520;-3.65900;,
 -18.45900;24.71332;-9.65900;,
 -18.45900;9.72050;-9.65900;,
 -18.45900;24.71332;-7.65900;,
 -18.45900;9.72050;-7.65900;,
 -18.45900;24.71332;10.34100;,
 -18.45900;24.71332;8.34100;,
 -25.38720;25.65752;4.34100;,
 -27.11925;25.65752;5.34100;,
 -18.45900;9.72106;10.34100;,
 -27.11925;10.14520;5.34100;,
 -25.38720;10.14520;4.34100;,
 -18.45900;9.72106;8.34100;,
 -25.38720;25.65752;-3.65900;,
 -27.11925;25.65752;-4.65900;,
 -27.11925;10.14520;-4.65900;,
 -25.38720;10.14520;-3.65900;,
 -18.45900;24.71332;-7.65900;,
 -18.45900;24.71332;-9.65900;,
 -18.45900;9.72050;-9.65900;,
 -18.45900;9.72050;-7.65900;,
 -18.45900;24.71332;-7.64635;,
 -18.45900;9.72050;-7.64635;,
 -18.45900;9.72050;-9.69344;,
 -18.45900;24.71332;-9.69344;,
 -18.45900;24.71332;10.35927;,
 -18.45900;9.72106;10.35927;,
 -18.45900;9.72106;8.33249;,
 -18.45900;24.71332;8.33249;,
 7.49486;22.83820;-7.18448;,
 34.95241;10.74914;-4.46284;,
 34.95241;7.03298;-4.46284;,
 7.49486;18.57301;-7.18448;,
 34.95241;10.74914;5.14484;,
 7.49486;22.83820;7.86648;,
 7.49486;18.57301;7.86648;,
 34.95241;7.03298;5.14484;,
 7.49486;22.83820;7.86648;,
 7.49486;22.83820;-7.18448;,
 7.49486;18.57301;-7.18448;,
 7.49486;18.57301;7.86648;,
 34.95241;10.74914;5.14484;,
 34.95241;10.74914;-4.46284;,
 7.49486;22.83820;-7.18448;,
 7.49486;18.57301;-7.18448;,
 34.95241;7.03298;-4.46284;,
 34.95241;7.03298;5.14484;,
 7.60286;20.72189;-1.02065;,
 7.57440;19.74167;-0.62702;,
 4.81418;19.80677;-0.66453;,
 4.84264;20.78699;-1.05816;,
 7.55141;19.32708;0.34465;,
 4.79119;19.39217;0.30715;,
 7.54738;19.72095;1.32517;,
 4.78716;19.78606;1.28766;,
 7.56465;20.69258;1.74016;,
 4.80443;20.75767;1.70265;,
 7.59312;21.67278;1.34653;,
 4.83290;21.73789;1.30902;,
 7.61611;22.08739;0.37486;,
 4.85589;22.15249;0.33735;,
 7.62013;21.69351;-0.60566;,
 4.85992;21.75861;-0.64317;,
 7.60286;20.72189;-1.02065;,
 4.84264;20.78699;-1.05816;,
 7.58376;20.70724;0.35975;,
 7.58376;20.70724;0.35975;,
 7.58376;20.70724;0.35975;,
 7.58376;20.70724;0.35975;,
 7.58376;20.70724;0.35975;,
 7.58376;20.70724;0.35975;,
 7.58376;20.70724;0.35975;,
 7.58376;20.70724;0.35975;,
 4.82354;20.77233;0.32225;,
 4.82354;20.77233;0.32225;,
 4.82354;20.77233;0.32225;,
 4.82354;20.77233;0.32225;,
 4.82354;20.77233;0.32225;,
 4.82354;20.77233;0.32225;,
 4.82354;20.77233;0.32225;,
 4.82354;20.77233;0.32225;,
 4.85727;20.80507;-2.91396;,
 4.80297;18.49861;-1.95563;,
 2.18841;18.20812;-2.05240;,
 2.24270;20.91481;-3.01073;,
 4.78049;17.54324;0.35796;,
 2.16592;17.25275;0.26119;,
 4.80297;18.49861;2.67155;,
 2.18841;18.20812;2.57478;,
 4.85727;20.80507;3.62987;,
 2.24270;20.91481;3.53311;,
 4.91156;23.11152;2.67155;,
 2.29699;23.22126;2.57478;,
 4.93405;24.06690;0.35796;,
 2.31949;24.17663;0.26119;,
 4.91156;23.11152;-1.95563;,
 2.29699;23.22126;-2.05240;,
 4.85727;20.80507;-2.91396;,
 2.24270;20.91481;-3.01073;,
 4.85727;20.80507;0.35796;,
 4.85727;20.80507;0.35796;,
 4.85727;20.80507;0.35796;,
 4.85727;20.80507;0.35796;,
 4.85727;20.80507;0.35796;,
 4.85727;20.80507;0.35796;,
 4.85727;20.80507;0.35796;,
 4.85727;20.80507;0.35796;,
 2.24270;20.88502;0.26119;,
 2.24270;20.88502;0.26119;,
 2.24270;20.88502;0.26119;,
 2.24270;20.88502;0.26119;,
 2.24270;20.88502;0.26119;,
 2.24270;20.88502;0.26119;,
 2.24270;20.88502;0.26119;,
 2.24270;20.88502;0.26119;;
 
 180;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 3;16,17,18;,
 3;19,20,17;,
 3;21,22,20;,
 3;23,24,22;,
 3;25,26,24;,
 3;27,28,26;,
 3;29,30,28;,
 3;31,32,30;,
 3;33,34,35;,
 3;36,35,37;,
 3;38,37,39;,
 3;40,39,41;,
 3;42,41,43;,
 3;44,43,45;,
 3;46,45,47;,
 3;48,47,49;,
 4;50,51,52,53;,
 4;51,54,55,52;,
 4;54,56,57,55;,
 4;56,58,59,57;,
 4;58,60,61,59;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,66,67,65;,
 3;68,51,50;,
 3;69,54,51;,
 3;70,56,54;,
 3;71,58,56;,
 3;72,60,58;,
 3;73,62,60;,
 3;74,64,62;,
 3;75,66,64;,
 3;76,53,52;,
 3;77,52,55;,
 3;78,55,57;,
 3;79,57,59;,
 3;80,59,61;,
 3;81,61,63;,
 3;82,63,65;,
 3;83,65,67;,
 4;84,85,86,87;,
 4;85,88,89,86;,
 4;88,90,91,89;,
 4;90,92,93,91;,
 4;92,94,95,93;,
 4;94,96,97,95;,
 4;96,98,99,97;,
 4;98,100,101,99;,
 3;102,85,84;,
 3;103,88,85;,
 3;104,90,88;,
 3;105,92,90;,
 3;106,94,92;,
 3;107,96,94;,
 3;108,98,96;,
 3;109,100,98;,
 3;110,87,86;,
 3;111,86,89;,
 3;112,89,91;,
 3;113,91,93;,
 3;114,93,95;,
 3;115,95,97;,
 3;116,97,99;,
 3;117,99,101;,
 4;118,119,120,121;,
 4;119,122,123,120;,
 4;124,125,126,127;,
 4;125,128,129,126;,
 4;128,130,131,129;,
 4;130,132,133,131;,
 3;134,119,118;,
 3;135,122,119;,
 3;136,137,122;,
 3;138,124,137;,
 3;139,125,124;,
 3;140,128,125;,
 3;141,130,128;,
 3;142,132,130;,
 3;143,121,120;,
 3;144,120,123;,
 3;145,123,146;,
 3;147,146,127;,
 3;148,127,126;,
 3;149,126,129;,
 3;150,129,131;,
 3;151,131,133;,
 4;152,153,154,155;,
 4;156,157,158,159;,
 4;156,153,160,161;,
 4;162,163,154,159;,
 4;164,165,166,167;,
 4;168,169,170,171;,
 4;172,173,174,175;,
 4;172,169,176,177;,
 4;178,179,170,175;,
 4;180,181,182,183;,
 4;184,185,186,187;,
 4;188,189,190,191;,
 4;188,181,192,193;,
 4;194,195,182,191;,
 4;196,197,198,199;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;204,208,209,210;,
 4;211,212,213,207;,
 4;214,215,216,217;,
 4;218,219,220,221;,
 4;215,222,223,216;,
 4;224,218,221,225;,
 4;222,226,227,223;,
 4;228,224,225,229;,
 4;230,231,232,233;,
 4;234,235,236,237;,
 4;233,232,238,239;,
 4;235,240,241,236;,
 4;239,238,242,243;,
 4;240,244,245,241;,
 4;246,247,248,249;,
 4;250,251,252,253;,
 4;254,255,256,257;,
 4;258,259,260,261;,
 4;262,263,264,265;,
 4;262,266,267,268;,
 4;269,270,271,265;,
 4;272,273,274,275;,
 4;273,276,277,274;,
 4;276,278,279,277;,
 4;278,280,281,279;,
 4;280,282,283,281;,
 4;282,284,285,283;,
 4;284,286,287,285;,
 4;286,288,289,287;,
 3;290,273,272;,
 3;291,276,273;,
 3;292,278,276;,
 3;293,280,278;,
 3;294,282,280;,
 3;295,284,282;,
 3;296,286,284;,
 3;297,288,286;,
 3;298,275,274;,
 3;299,274,277;,
 3;300,277,279;,
 3;301,279,281;,
 3;302,281,283;,
 3;303,283,285;,
 3;304,285,287;,
 3;305,287,289;,
 4;306,307,308,309;,
 4;307,310,311,308;,
 4;310,312,313,311;,
 4;312,314,315,313;,
 4;314,316,317,315;,
 4;316,318,319,317;,
 4;318,320,321,319;,
 4;320,322,323,321;,
 3;324,307,306;,
 3;325,310,307;,
 3;326,312,310;,
 3;327,314,312;,
 3;328,316,314;,
 3;329,318,316;,
 3;330,320,318;,
 3;331,322,320;,
 3;332,309,308;,
 3;333,308,311;,
 3;334,311,313;,
 3;335,313,315;,
 3;336,315,317;,
 3;337,317,319;,
 3;338,319,321;,
 3;339,321,323;;
 
 MeshMaterialList {
  7;
  180;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6;;
  Material {
   0.796800;0.800000;0.772000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Pictures\\black.PNG";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  192;
  0.003115;-0.006340;0.999975;,
  0.922908;0.385021;-0.000433;,
  0.924837;-0.380328;-0.005292;,
  0.385008;-0.922886;-0.007050;,
  -0.380351;-0.924830;-0.004679;,
  -0.922907;-0.385022;0.000433;,
  -0.924836;0.380329;0.005292;,
  -0.385008;0.922886;0.007051;,
  0.380352;0.924830;0.004679;,
  -0.003115;0.006340;-0.999975;,
  0.003116;-0.006340;0.999975;,
  0.003115;-0.006340;0.999975;,
  0.003115;-0.006340;0.999975;,
  0.003115;-0.006340;0.999975;,
  0.003114;-0.006340;0.999975;,
  0.003115;-0.006340;0.999975;,
  0.003115;-0.006339;0.999975;,
  0.003115;-0.006339;0.999975;,
  -0.003115;0.006340;-0.999975;,
  -0.003116;0.006340;-0.999975;,
  -0.003115;0.006340;-0.999975;,
  -0.003115;0.006340;-0.999975;,
  -0.003114;0.006340;-0.999975;,
  -0.003115;0.006340;-0.999975;,
  -0.003115;0.006339;-0.999975;,
  -0.003115;0.006339;-0.999975;,
  0.003115;-0.006340;0.999975;,
  0.922908;0.385021;-0.000433;,
  0.924837;-0.380328;-0.005292;,
  0.385008;-0.922886;-0.007050;,
  -0.380351;-0.924830;-0.004679;,
  -0.922907;-0.385022;0.000433;,
  -0.924836;0.380329;0.005292;,
  -0.385008;0.922886;0.007051;,
  0.380352;0.924830;0.004679;,
  -0.003115;0.006340;-0.999975;,
  0.003116;-0.006340;0.999975;,
  0.003115;-0.006339;0.999975;,
  0.003115;-0.006340;0.999975;,
  0.003115;-0.006340;0.999975;,
  0.003114;-0.006340;0.999975;,
  0.003115;-0.006340;0.999975;,
  0.003116;-0.006339;0.999975;,
  0.003115;-0.006338;0.999975;,
  -0.003115;0.006339;-0.999975;,
  -0.003116;0.006340;-0.999975;,
  -0.003116;0.006340;-0.999975;,
  -0.003115;0.006340;-0.999975;,
  -0.003114;0.006340;-0.999975;,
  -0.003114;0.006340;-0.999975;,
  -0.003115;0.006339;-0.999975;,
  -0.003115;0.006338;-0.999975;,
  0.004289;-0.009363;0.999947;,
  0.922908;0.385021;-0.000315;,
  0.925808;-0.377953;-0.005632;,
  0.387346;-0.921849;-0.012586;,
  -0.383220;-0.923589;-0.011235;,
  -0.924090;-0.382170;-0.001847;,
  -0.924842;0.380332;0.003845;,
  -0.385013;0.922897;0.005123;,
  0.380352;0.924836;0.003400;,
  -0.004286;0.008723;-0.999953;,
  0.002628;-0.009103;0.999955;,
  0.003004;-0.009257;0.999953;,
  0.003382;-0.009101;0.999953;,
  0.005194;-0.009098;0.999945;,
  0.005952;-0.009096;0.999941;,
  0.005573;-0.009250;0.999942;,
  0.004819;-0.009999;0.999938;,
  0.003761;-0.010000;0.999943;,
  -0.004284;0.008724;-0.999953;,
  -0.004285;0.008723;-0.999953;,
  -0.004286;0.008721;-0.999953;,
  -0.004287;0.008721;-0.999953;,
  -0.004288;0.008723;-0.999953;,
  -0.004288;0.008725;-0.999953;,
  -0.004288;0.008726;-0.999953;,
  -0.004286;0.008725;-0.999953;,
  0.004287;-0.008723;0.999953;,
  0.922907;0.385023;-0.000314;,
  0.924842;-0.380332;-0.003845;,
  0.708888;-0.705304;-0.004854;,
  0.004287;-0.008725;0.999953;,
  -0.999994;-0.002540;0.002251;,
  -0.924842;0.380332;0.003845;,
  -0.385013;0.922897;0.005123;,
  0.380352;0.924836;0.003400;,
  -0.004286;0.008723;-0.999953;,
  -0.004287;0.008723;-0.999953;,
  0.004289;-0.008725;0.999953;,
  0.004288;-0.008724;0.999953;,
  0.004289;-0.008725;0.999953;,
  0.004285;-0.008724;0.999953;,
  0.004285;-0.008722;0.999953;,
  0.004286;-0.008721;0.999953;,
  0.004287;-0.008721;0.999953;,
  -0.004288;0.008723;-0.999953;,
  -0.004288;0.008724;-0.999953;,
  -0.004288;0.008724;-0.999953;,
  -0.004284;0.008723;-0.999953;,
  -0.004285;0.008723;-0.999953;,
  -0.004286;0.008722;-0.999953;,
  -0.004287;0.008721;-0.999953;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.272690;0.962102;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.891557;0.000000;-0.452908;,
  -0.951815;0.000000;0.306674;,
  0.295972;0.939318;-0.173443;,
  0.000000;-0.999999;-0.001377;,
  -0.958582;0.000000;-0.284815;,
  0.874776;0.000000;0.484528;,
  0.000000;0.000000;1.000000;,
  0.316690;0.939724;0.128944;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.036249;0.999343;0.000000;,
  -0.036249;-0.999343;0.000000;,
  -0.500000;0.000000;-0.866025;,
  -0.500000;0.000000;0.866025;,
  -1.000000;0.000000;0.000000;,
  0.500000;0.000000;0.866025;,
  0.500000;0.000000;-0.866025;,
  1.000000;0.000000;0.000000;,
  0.094796;0.994386;0.047022;,
  0.047465;0.998595;0.023544;,
  -0.042799;-0.998859;-0.021190;,
  -0.021405;-0.999715;-0.010598;,
  0.044122;0.998595;-0.029333;,
  -0.021434;-0.999714;0.010612;,
  0.088120;0.994386;-0.058585;,
  -0.042855;-0.998856;0.021218;,
  0.098638;0.000000;-0.995123;,
  0.098638;0.000000;0.995123;,
  -1.000000;0.000000;0.000000;,
  0.402955;0.915220;0.000000;,
  -0.387457;-0.921888;0.000000;,
  0.999630;-0.023576;0.013584;,
  0.013838;0.010620;-0.999848;,
  -0.006781;-0.699364;-0.714734;,
  -0.023428;-0.999666;-0.010932;,
  -0.026351;-0.714375;0.699266;,
  -0.013838;-0.010618;0.999848;,
  0.006783;0.699361;0.714736;,
  0.023430;0.999666;0.010938;,
  0.026351;0.714376;-0.699266;,
  -0.999630;0.023577;-0.013585;,
  0.999723;-0.023533;-0.000000;,
  0.051257;0.012311;-0.998610;,
  0.087660;-0.695493;-0.713165;,
  0.110399;-0.993887;0.000713;,
  0.035041;-0.697470;0.715757;,
  -0.022649;0.013866;0.999647;,
  0.003572;0.707913;0.706290;,
  0.041930;0.999121;0.000099;,
  0.055763;0.706204;-0.705809;,
  -0.999758;0.022005;0.000000;,
  0.999630;-0.023574;0.013586;,
  0.999630;-0.023569;0.013581;,
  0.999630;-0.023579;0.013586;,
  0.999630;-0.023575;0.013584;,
  0.999630;-0.023574;0.013588;,
  0.999630;-0.023579;0.013589;,
  0.999630;-0.023580;0.013580;,
  0.999630;-0.023574;0.013576;,
  -0.999630;0.023574;-0.013581;,
  -0.999630;0.023575;-0.013586;,
  -0.999630;0.023579;-0.013586;,
  -0.999630;0.023576;-0.013585;,
  -0.999630;0.023574;-0.013588;,
  -0.999630;0.023578;-0.013590;,
  -0.999630;0.023579;-0.013586;,
  -0.999630;0.023579;-0.013581;,
  0.999723;-0.023534;-0.000002;,
  0.999723;-0.023534;-0.000000;,
  0.999723;-0.023532;-0.000000;,
  0.999723;-0.023534;0.000002;,
  0.999723;-0.023534;-0.000000;,
  0.999723;-0.023532;0.000000;,
  0.999723;-0.023532;-0.000000;,
  -0.999763;0.021781;0.000198;,
  -0.999787;0.020626;-0.000404;,
  -0.999777;0.021134;0.000000;,
  -0.999787;0.020626;0.000404;,
  -0.999763;0.021781;-0.000198;,
  -0.999727;0.023383;-0.000153;,
  -0.999728;0.023323;0.000000;,
  -0.999727;0.023383;0.000153;;
  180;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,10,11;,
  3;0,12,10;,
  3;0,13,12;,
  3;0,14,13;,
  3;0,15,14;,
  3;0,16,15;,
  3;0,17,16;,
  3;0,11,17;,
  3;9,18,19;,
  3;9,19,20;,
  3;9,20,21;,
  3;9,21,22;,
  3;9,22,23;,
  3;9,23,24;,
  3;9,24,25;,
  3;9,25,18;,
  4;27,28,28,27;,
  4;28,29,29,28;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,32,32,31;,
  4;32,33,33,32;,
  4;33,34,34,33;,
  4;34,27,27,34;,
  3;26,36,37;,
  3;26,38,36;,
  3;26,39,38;,
  3;26,40,39;,
  3;26,41,40;,
  3;26,42,41;,
  3;26,43,42;,
  3;26,37,43;,
  3;35,44,45;,
  3;35,45,46;,
  3;35,46,47;,
  3;35,47,48;,
  3;35,48,49;,
  3;35,49,50;,
  3;35,50,51;,
  3;35,51,44;,
  4;53,54,54,53;,
  4;54,55,55,54;,
  4;55,56,56,55;,
  4;56,57,57,56;,
  4;57,58,58,57;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;60,53,53,60;,
  3;52,62,63;,
  3;52,64,62;,
  3;52,65,64;,
  3;52,66,65;,
  3;52,67,66;,
  3;52,68,67;,
  3;52,69,68;,
  3;52,63,69;,
  3;61,70,71;,
  3;61,71,72;,
  3;61,72,73;,
  3;61,73,74;,
  3;61,74,75;,
  3;61,75,76;,
  3;61,76,77;,
  3;61,77,70;,
  4;79,80,80,79;,
  4;80,81,81,80;,
  4;83,84,84,83;,
  4;84,85,85,84;,
  4;85,86,86,85;,
  4;86,79,79,86;,
  3;78,89,90;,
  3;78,91,89;,
  3;78,82,91;,
  3;78,92,82;,
  3;78,93,92;,
  3;78,94,93;,
  3;78,95,94;,
  3;78,90,95;,
  3;88,96,97;,
  3;88,97,98;,
  3;88,98,87;,
  3;88,87,99;,
  3;88,99,100;,
  3;88,100,101;,
  3;88,101,102;,
  3;88,102,96;,
  4;104,104,104,104;,
  4;103,103,103,103;,
  4;105,105,105,105;,
  4;106,106,106,106;,
  4;107,107,107,107;,
  4;108,108,108,108;,
  4;109,109,109,109;,
  4;110,110,110,110;,
  4;111,111,111,111;,
  4;113,113,113,113;,
  4;114,114,114,114;,
  4;112,112,112,112;,
  4;115,115,115,115;,
  4;116,116,116,116;,
  4;117,117,117,117;,
  4;118,118,118,118;,
  4;119,119,119,119;,
  4;120,120,120,120;,
  4;121,121,121,121;,
  4;123,123,123,123;,
  4;126,126,126,126;,
  4;124,124,124,124;,
  4;127,127,127,127;,
  4;122,122,122,122;,
  4;125,125,125,125;,
  4;128,128,129,129;,
  4;130,131,131,130;,
  4;129,129,132,132;,
  4;131,133,133,131;,
  4;132,132,134,134;,
  4;133,135,135,133;,
  4;127,127,127,127;,
  4;127,127,127,127;,
  4;136,136,136,136;,
  4;137,137,137,137;,
  4;138,138,138,138;,
  4;139,139,139,139;,
  4;140,140,140,140;,
  4;142,143,143,142;,
  4;143,144,144,143;,
  4;144,145,145,144;,
  4;145,146,146,145;,
  4;146,147,147,146;,
  4;147,148,148,147;,
  4;148,149,149,148;,
  4;149,142,142,149;,
  3;141,161,162;,
  3;141,163,161;,
  3;141,164,163;,
  3;141,165,164;,
  3;141,166,165;,
  3;141,167,166;,
  3;141,168,167;,
  3;141,162,168;,
  3;150,169,170;,
  3;150,170,171;,
  3;150,171,172;,
  3;150,172,173;,
  3;150,173,174;,
  3;150,174,175;,
  3;150,175,176;,
  3;150,176,169;,
  4;152,153,153,152;,
  4;153,154,154,153;,
  4;154,155,155,154;,
  4;155,156,156,155;,
  4;156,157,157,156;,
  4;157,158,158,157;,
  4;158,159,159,158;,
  4;159,152,152,159;,
  3;151,177,178;,
  3;151,179,177;,
  3;151,180,179;,
  3;151,181,180;,
  3;151,182,181;,
  3;151,179,182;,
  3;151,183,179;,
  3;151,178,183;,
  3;160,184,185;,
  3;160,185,186;,
  3;160,186,187;,
  3;160,187,188;,
  3;160,188,189;,
  3;160,189,190;,
  3;160,190,191;,
  3;160,191,184;;
 }
 MeshTextureCoords {
  340;
  -0.445646;-0.159267;,
  -0.444681;0.223407;,
  -0.446015;0.220691;,
  -0.446980;-0.161982;,
  -0.714595;0.494685;,
  -0.715930;0.491970;,
  -1.097275;0.495657;,
  -1.098609;0.492941;,
  -1.368553;0.225754;,
  -1.369887;0.223038;,
  -1.369517;-0.156920;,
  -1.370851;-0.159636;,
  -1.099603;-0.428198;,
  -1.100937;-0.430914;,
  -0.716923;-0.429171;,
  -0.718256;-0.431886;,
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;0.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.500000;1.000000;,
  0.666670;0.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.666670;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;;
 }
}
