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
	FILE *fp;
	char tmp[256];
	Image img;
	unsigned int x, y;

	fp = fopen(av[1], "rb");
	if (fp == NULL) {
		cout << "入力ファイルがありません" << endl;
		exit(8);
	}
	fgets(tmp, 256, fp);
	cout << "Magic Number = ";
	cout << tmp[0];
	cout << tmp[1] << endl;

	fgets(tmp, 256, fp);
	sscanf(tmp,"%d %d",&img.width, &img.height);
	cout <<"Image width = "<< img.width << endl;
	cout<< "Image height = " << img.height << endl;
	vector<vector<unsigned char>> value(img.height, vector<unsigned char>(img.width));

	fgets(tmp, 256, fp);
	sscanf(tmp, "%d", &img.max_value);
	cout << "Maximum brightness value = " << img.max_value << endl << endl;

	for (int y = 0; y < img.height; y++) {
		for (int x = 0; x < img.width; x++) {
			value[y][x] = (unsigned char)fgetc(fp);
		}
	}

	cout << "取得したい輝度値の座標を入力してください" << endl;
	cin >> x >> y;
	cout << "(x,y) = (" << x << ", " << y << ") 座標の輝度値は" << (int)value[y][x] << endl;

	fclose(fp);

	return 0;
}