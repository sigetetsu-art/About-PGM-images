#include <iostream>
#include <stdlib.h>
#include <vector>
#pragma warning(disable:4996)

using namespace std;

class Image {
public:
	int width;
	int height;
	int max_value;
	Image();
};

Image::Image() {
	width = 0;
	height = 0;
	max_value = 0;
}



int main(int ac, char *av[]) {
	FILE* fp, *fo;
	char tmp[256];
	Image img;

	fp = fopen(av[1], "rb");
	if (fp == NULL) {
		cout << "入力ファイルがありません" << endl;
		exit(8);
	}
	fo = fopen(av[2], "wb");
	if (fo == NULL) {
		cout << "出力ファイルがありません" << endl;
		exit(8);
	}

	fgets(tmp, 256, fp);
	fprintf(fo, "P5\n");
	
	cout << "Magic Number = ";
	cout << tmp[0];
	cout << tmp[1] << endl;

	fgets(tmp, 256, fp);
	sscanf(tmp, "%d %d", &img.width, &img.height);
	cout << "Image width = " << img.width << endl;
	cout << "Image height = " << img.height << endl;
	vector<vector<unsigned char>> value(img.height, vector<unsigned char>(img.width));

	fgets(tmp, 256, fp);
	sscanf(tmp, "%d", &img.max_value);
	cout << "Maximum brightness value = " << img.max_value << endl << endl;

	fprintf(fo, "%d %d\n%d\n", img.width, img.height, img.max_value);

	for (int y = 0; y < img.height; y++) {
		for (int x = 0; x < img.width; x++) {
			value[y][x] = (unsigned char)fgetc(fp);
		}
	}

	for (int y = 0; y < img.height; y++) {
		for (int x = 0; x < img.width; x++) {
			if (value[y][x] * 2 > 255) {
				value[y][x] = 255;
			}
			else {
				value[y][x] = value[y][x] * 2;
			}
			fputc(value[y][x], fo);
		}
	}

	fclose(fp);
	fclose(fo);

	return 0;
}
