/*
in

ifstream fin("input.bmp", ios::binary);
auto img = image_func(fin);
fin.close();

##########
out

saveBMP("output.bmp", img);
*/


#pragma once
#include <iostream>
#include <fstream>
#include <vector>
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
using namespace std;

#pragma pack(push,1)
struct BITMAPFILEHEADER {
    uint16_t bfType;       
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};
struct BITMAPCOREHEADER {
    uint32_t bcSize;
};
#pragma pack(pop)


struct BMP {
    int width;
    int height;
    int bpp;
    vector<uint8_t> pixels; // raw BGR
};


BMP loadBMP(ifstream& fin){
    // for(int i=0;i<10;i++){
    //     string str;
    //     fin>>str;
    //     getline(fin,str);
    //     cout<<str;
    // }
    // ifstream fin(filename, ios::binary);
    // if(!fin) throw runtime_error("File open failed");

    BITMAPFILEHEADER fh;
    fin.read((char*)&fh, sizeof(fh));

    // BMP signature check
    if (fh.bfType != 0x4D42)
        throw runtime_error("NOT a BMP file");

    // read info header size only
    BITMAPCOREHEADER core;
    fin.read((char*)&core, sizeof(core));

    uint32_t headerSize = core.bcSize;

    if(headerSize < 12)
        throw runtime_error("invalid header size");

    vector<char> info(headerSize);
    *(uint32_t*)info.data() = headerSize;

    // read entire infoheader area
    fin.read(info.data()+4, headerSize-4);

    // parse values
    int32_t width, height;
    uint16_t planes, bitcount;
    uint32_t compression;

    if(headerSize >= 40){
        // BITMAPINFOHEADER or later
        width       = *(int32_t*)(info.data()+4);
        height      = *(int32_t*)(info.data()+8);
        planes      = *(uint16_t*)(info.data()+12);
        bitcount    = *(uint16_t*)(info.data()+14);
        compression = *(uint32_t*)(info.data()+16);
    }else{
        throw runtime_error("OS/2 BMP unsupported");
    }

    if(compression != 0)
        throw runtime_error("compressed BMP unsupported");

    int Bpp = bitcount / 8;
    if(Bpp != 3)
        throw runtime_error("only 24bit supported");

    int W = width;
    int H = abs(height);

    BMP bmp;
    bmp.width = W;
    bmp.height = H;
    bmp.bpp = bitcount;
    bmp.pixels.resize(W * H * 3);

    fin.seekg(fh.bfOffBits, ios::beg);

    int rowSize = ((W*3 + 3)/4)*4;
    vector<uint8_t> row(rowSize);

    for(int y=0;y<H;y++){
        int rowIndex = (height>0? (H-1-y) : y);

        fin.read((char*)row.data(), rowSize);

        for(int x=0;x<W;x++){
            bmp.pixels[(rowIndex*W + x)*3 + 0] = row[x*3+0];
            bmp.pixels[(rowIndex*W + x)*3 + 1] = row[x*3+1];
            bmp.pixels[(rowIndex*W + x)*3 + 2] = row[x*3+2];
        }
    }

    return bmp;
}

vector<vector<double>> image_func(ifstream& fin){
    
    auto bmp = loadBMP(fin);

    // cout<<"W = "<<bmp.width<<"\n";
    // cout<<"H = "<<bmp.height<<"\n";
    // cout<<"bpp = "<<bmp.bpp<<"\n";

    // // 픽셀 예시 출력
    // for(int i=0;i<10;i++){
    //     cout<<(int)bmp.pixels[i]<<" ";
    // }
    // 픽셀 예시 출력
    // string tmp="image_func.txt";
    // ofstream fout(tmp);
    vector<vector<double>> answer;
    for(int y=0;y<bmp.height;y++){
        answer.push_back(vector<double>());
        for(int x=0;x<bmp.width;x++){
            answer[y].resize(bmp.width);
            // answer[y].push_back(vector<double>());
            int idx = (y*bmp.width + x) * (bmp.bpp/8);
            // unsigned int B = bmp.pixels[idx+0];
            // unsigned int G = bmp.pixels[idx+1];
            // unsigned int R = bmp.pixels[idx+2];
            double B = bmp.pixels[idx+0];
            double G = bmp.pixels[idx+1];
            double R = bmp.pixels[idx+2];
            // fout<<(int)R<<" "; 255
            // cout<<R<<G<<B;
            // fout<<(R+G+B)/(3*255)<<" ";
            // fout<<"("<<(int)R<<","<<(int)G<<","<<(int)B<<") ";
            // fout<<(int)((R+G+B)/(3*255)*100)<<" ";
            answer[y][x]=min(1.0,(1-(R+G+B)/(3*255)));
            // answer[y][x]=((double)1-(R+G+B)/(3*255)*2);
        }
        // fout<<"\n";
    }
    return answer;
}

void saveBMP(const string& filename, const vector<vector<double>>& img) {
    int H = img.size();
    int W = img[0].size();

    int rowSize = ((W * 3 + 3) / 4) * 4; // padding 포함
    int pixelDataSize = rowSize * H;

    BITMAPFILEHEADER fh;
    fh.bfType = 0x4D42; // 'BM'
    fh.bfOffBits = sizeof(BITMAPFILEHEADER) + 40;
    fh.bfSize = fh.bfOffBits + pixelDataSize;
    fh.bfReserved1 = 0;
    fh.bfReserved2 = 0;

    // BITMAPINFOHEADER 직접 구성
    uint32_t biSize = 40;
    int32_t biWidth = W;
    int32_t biHeight = H; // bottom-up
    uint16_t biPlanes = 1;
    uint16_t biBitCount = 24;
    uint32_t biCompression = 0;
    uint32_t biSizeImage = pixelDataSize;
    int32_t biXPelsPerMeter = 0;
    int32_t biYPelsPerMeter = 0;
    uint32_t biClrUsed = 0;
    uint32_t biClrImportant = 0;

    ofstream fout(filename, ios::binary);
    if (!fout) throw runtime_error("File open failed");

    // file header
    fout.write((char*)&fh, sizeof(fh));

    // info header
    fout.write((char*)&biSize, 4);
    fout.write((char*)&biWidth, 4);
    fout.write((char*)&biHeight, 4);
    fout.write((char*)&biPlanes, 2);
    fout.write((char*)&biBitCount, 2);
    fout.write((char*)&biCompression, 4);
    fout.write((char*)&biSizeImage, 4);
    fout.write((char*)&biXPelsPerMeter, 4);
    fout.write((char*)&biYPelsPerMeter, 4);
    fout.write((char*)&biClrUsed, 4);
    fout.write((char*)&biClrImportant, 4);

    vector<uint8_t> row(rowSize);

    for (int y = 0; y < H; y++) {
        int rowIndex = H - 1 - y; // BMP는 뒤집어서 저장

        for (int x = 0; x < W; x++) {
            double v = img[rowIndex][x];

            // clamp
            if (v < 0) v = 0;
            if (v > 1) v = 1;

            uint8_t gray = (uint8_t)(v * 255.0);

            row[x * 3 + 0] = gray; // B
            row[x * 3 + 1] = gray; // G
            row[x * 3 + 2] = gray; // R
        }

        // padding 영역 0으로
        for (int i = W * 3; i < rowSize; i++)
            row[i] = 0;

        fout.write((char*)row.data(), rowSize);
    }

    fout.close();
}