// test1.cpp : �������̨Ӧ�ó������ڵ㡣

#include "stdafx.h"
#include "cv.h"
#include "highgui.h"
#include <algorithm>
#include <iostream>
#include "baseapi.h"
using namespace std;
//ԭͼ
IplImage *img;
//������
IplImage *img2, *img3, *img4, *img5, *img6;
IplImage* img7[5];

void onchange(int i)
{
	cvAdaptiveThreshold( img2, img4, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, i%2==0?i+5:i+4);
	cvShowImage("Example4", img4);
}

void onchange2(int i)
{
	cvThreshold(img2, img5, i , 255, CV_THRESH_BINARY);
	cvShowImage("Example5", img5);
}

void onchange3(int i)
{
	if (!i)return;
	if (!(i&1))++i;
	cvSmooth(img3, img6, CV_MEDIAN, i, i);
	//cvSmooth(img3, img6, CV_BLUR, i, i);
	cvShowImage("Example6", img6);
}
int e1=1, e2=1, e3=1;
void onchange74(int i)
{
	if (!(e1 && e2 && e3)) return;
	//img7[4] = cvCreateImage(cvGetSize(img3), IPL_DEPTH_8U, 3);  //������ͨ��ͼ��  
    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* lines = 0;
    //cvCanny( src, dst, 50, 100, 3);  //�������б�Ե��⣬����ԻҶ�ͼ��ʾ��ֻ�б�Ե)
    cvCvtColor( img3, img7[4], CV_GRAY2BGR); //ɫ�ʿռ�ת������dstת��������һ��ɫ�ʿռ伴3ͨ��ͼ��
    cvNot(img3, img3);
	lines = cvHoughLines2(img3, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, e1, e2, e3); //ֱ�ӵõ�ֱ������
    cvNot(img3, img3);
	//ѭ��ֱ������
    for(int i = 0; i < lines ->total; i++)//lines�洢����ֱ��
    {
        CvPoint* line = ( CvPoint* )cvGetSeqElem(lines, i);//lines��������洢�������ص�����  
        cvLine( img7[4], line[0], line[1], CV_RGB( 0, 255, 0));//���ҵ���ֱ�߱��Ϊlvɫ  
        //color_dst����ͨ��ͼ��������ֱ��ͼ��
    }
	cvShowImage("Example7[4]", img7[4]);
}


//==========================================
//��Ȩƽ���ҶȻ�
void convertToGrayWAve(IplImage* in, IplImage*& out)
{
	out = cvCreateImage(cvGetSize(in), in->depth, 1);
	for (int i = 0; i < in->height; ++i)
		for (int j = 0; j < in->width; ++j)
		{
			uchar* pin = (uchar*)in->imageData + i * in->widthStep + j * in->nChannels;
			uchar* pout = (uchar*)out->imageData + i * out->widthStep + j;
			pout[0] = 0.114*pin[0] + 0.587*pin[1] + 0.299*pin[2];
		}
}
//ƽ��ֵ�ҶȻ�
void convertToGrayAve(IplImage* in, IplImage*& out)
{
	out = cvCreateImage(cvGetSize(in), in->depth, 1);
	for (int i = 0; i < in->height; ++i)
		for (int j = 0; j < in->width; ++j)
		{
			uchar* pin = (uchar*)in->imageData + i * in->widthStep + j * in->nChannels;
			uchar* pout = (uchar*)out->imageData + i * out->widthStep + j;
			pout[0] = (pin[0] + pin[1] + pin[2])/ 3.0;
		}
}
//���ֵ�ҶȻ�
void convertToGrayMax(IplImage* in, IplImage*& out)
{
	out = cvCreateImage(cvGetSize(in), in->depth, 1);
	for (int i = 0; i < in->height; ++i)
		for (int j = 0; j < in->width; ++j)
		{
			uchar* pin = (uchar*)in->imageData + i * in->widthStep + j * in->nChannels;
			uchar* pout = (uchar*)out->imageData + i * out->widthStep + j;
			pout[0] = max(max(pin[0], pin[1]), pin[2]);
		}
}
//��Сֵ�ҶȻ�
void convertToGrayMin(IplImage* in, IplImage*& out)
{
	out = cvCreateImage(cvGetSize(in), in->depth, 1);
	for (int i = 0; i < in->height; ++i)
		for (int j = 0; j < in->width; ++j)
		{
			uchar* pin = (uchar*)in->imageData + i * in->widthStep + j * in->nChannels;
			uchar* pout = (uchar*)out->imageData + i * out->widthStep + j;
			pout[0] = min(min(pin[0], pin[1]), pin[2]);
		}
}
//Rͨ���ҶȻ�
void convertToGrayR(IplImage* in, IplImage*& out)
{
	out = cvCreateImage(cvGetSize(in), in->depth, 1);
	for (int i = 0; i < in->height; ++i)
		for (int j = 0; j < in->width; ++j)
		{
			uchar* pin = (uchar*)in->imageData + i * in->widthStep + j * in->nChannels;
			uchar* pout = (uchar*)out->imageData + i * out->widthStep + j;
			pout[0] = pin[2];
		}
}
//Gͨ���ҶȻ�
void convertToGrayG(IplImage* in, IplImage*& out)
{
	out = cvCreateImage(cvGetSize(in), in->depth, 1);
	for (int i = 0; i < in->height; ++i)
		for (int j = 0; j < in->width; ++j)
		{
			uchar* pin = (uchar*)in->imageData + i * in->widthStep + j * in->nChannels;
			uchar* pout = (uchar*)out->imageData + i * out->widthStep + j;
			pout[0] = pin[1];
		}
}
//Bͨ���ҶȻ�
void convertToGrayB(IplImage* in, IplImage*& out)
{
	out = cvCreateImage(cvGetSize(in), in->depth, 1);
	for (int i = 0; i < in->height; ++i)
		for (int j = 0; j < in->width; ++j)
		{
			uchar* pin = (uchar*)in->imageData + i * in->widthStep + j * in->nChannels;
			uchar* pout = (uchar*)out->imageData + i * out->widthStep + j;
			pout[0] = pin[0];
		}
}
//�ҶȻ�Ч���Ա�
void grayShow()
{
	IplImage* gray[7];
	convertToGrayWAve(img, gray[0]);
	cvNamedWindow("��Ȩƽ��", 1);
	cvShowImage("��Ȩƽ��", gray[0]);

	convertToGrayAve(img, gray[1]);
	cvNamedWindow("ƽ��ֵ", 1);
	cvShowImage("ƽ��ֵ", gray[1]);

	convertToGrayMax(img, gray[2]);
	cvNamedWindow("���ֵ", 1);
	cvShowImage("���ֵ", gray[2]);

	convertToGrayMin(img, gray[3]);
	cvNamedWindow("��Сֵ", 1);
	cvShowImage("��Сֵ", gray[3]);

	convertToGrayR(img, gray[4]);
	cvNamedWindow("Rͨ��", 1);
	cvShowImage("Rͨ��", gray[4]);

	convertToGrayG(img, gray[5]);
	cvNamedWindow("Gͨ��", 1);
	cvShowImage("Gͨ��", gray[5]);

	convertToGrayB(img, gray[6]);
	cvNamedWindow("Bͨ��", 1);
	cvShowImage("Bͨ��", gray[6]);
}


//��ͨ��ͼ����߿�,��img[0][0]Ϊ���Ⱦ�෴ɫ
inline bool law(IplImage* img, int x, int y)
{
	return (x >= 0 && x < img->height && y >= 0 && y < img->width);
}

void clearFrame(IplImage* img, bool** map,int dir[][2], int x, int y)
{
	uchar* ptr = (uchar*)img->imageData;
	uchar gray = ptr[0];
	gray = 255 - gray;

	for (int i = 0; i < 4; ++i)
	{
		int tx = x + dir[i][0];
		int ty = y + dir[i][1];
		if(law(img, tx, ty))
		{
			uchar* p = ptr + tx*img->widthStep + ty;
			if (p[0] == ptr[0] && !map[tx][ty])
			{
				p[0] = gray;
				map[tx][ty] = true;
				clearFrame(img, map, dir, tx, ty);
			}
		}
	}
}

void clearFrameStarter(IplImage* img)
{
	bool** map = new bool*[img->height];
	for (int i = 0; i < img->height; ++i)
		map[i] = new bool[img->width];
	for (int i = 0; i < img->height; ++i)
		for (int j = 0; j < img->width; ++j)
			map[i][j] = false;
	map[0][0] = true;

	int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};

	clearFrame(img, map, dir, 0, 0);

	uchar* ptr = (uchar*)img->imageData;
	ptr[0] = 255 - ptr[0];
}

//OSTUȡ��ֵ
int otsu(IplImage *img)
{
    uchar* ptr = (uchar*)img->imageData;
	int threshold = 0, sum = img->width * img->height;
	int grayCnt[256];
	
	memset(grayCnt, 0, sizeof(grayCnt));

	for (int i = 0; i < img->height; ++i)
		for (int j = 0; j < img->width; ++j)
			++grayCnt[ptr[i*img->widthStep + j]];

	int sumGray = 0;
	for (int i = 0; i < 256; ++i)
		sumGray += i*grayCnt[i];
	double aveGray = sumGray*1.0 / sum;

	double maxTheta = 0;
	for (int i = 0; i < 256; ++i)
	{
		int a = 0, asum = 0, b = 0, bsum = 0;
		for (int j = 0; j < i; ++j)
		{
			a += grayCnt[j];
			asum += j*grayCnt[j];
		}
		for (int j = i; j < 256; ++j)
		{
			b += grayCnt[j];
			bsum += j*grayCnt[j];
		}
		double tmp = 0;
		if (a) tmp += a*1.0/sum*(asum*1.0/a - aveGray)*(asum*1.0/a - aveGray);
		if (b) tmp += b*1.0/sum*(bsum*1.0/b - aveGray)*(bsum*1.0/b - aveGray);
		if (tmp > maxTheta)
		{
			maxTheta = tmp;
			threshold = i;
		}
	}

	return threshold;
}

void dfs(IplImage* img, int cnt, int dir[][2], int** map, int x, int y)
{
	map[x][y] = cnt;
	uchar* ptr = (uchar*)img->imageData;
	for (int i = 0; i < 4; ++i)
	{
		int tx = x + dir[i][0];
		int ty = y + dir[i][1];
		if (law(img, tx, ty) && map[tx][ty] == -1
			&& ptr[tx*img->widthStep + ty] == ptr[x*img->widthStep+y])
		{
			dfs(img, cnt, dir, map, tx, ty);
		}
	}
}

//��ͨ��ȥ��
void antiNoise(IplImage* img, int t = 5)
{
	int** map = new int*[img->height];
	for (int i = 0; i < img->height; ++i)
		map[i] = new int[img->width];
	for (int i = 0; i < img->height; ++i)
		for (int j = 0; j < img->width; ++j)
			map[i][j] = -1;
	int cnt = 0;
	int dir[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
	uchar* ptr = (uchar*)img->imageData;

	for (int i = 0; i < img->height; ++i)
		for (int j = 0; j < img->width; ++j)
			if (map[i][j] == -1)
			{
				dfs(img, cnt, dir, map, i, j);
				++cnt;
			}
	int* area = new int[cnt];
	for (int i = 0; i < cnt; ++i) area[i] = 0;

	for (int i = 0; i < img->height; ++i)
		for (int j = 0; j < img->width; ++j)
			++area[map[i][j]];

	for (int i = 0; i < cnt; ++i)
		if (area[i] > t) area[i] = 0;

	for (int i = 0; i < img->height; ++i)
		for (int j = 0; j < img->width; ++j)
			if (area[map[i][j]])
			{
				ptr[i*img->widthStep+j] = 255;
			}
}

//��ֵ�˲�
void aveSmooth(IplImage* img, IplImage* &out)
{
	out = cvCreateImage(cvGetSize(img), img->depth, 1);
	int dir2[8][2] = {-1, -1, -1, 1, 1, -1, 1, 1, 0, -1, 0, 1, 1, 0, -1, 0};
	for (int i = 0; i < img->height; ++i)
		for (int j = 0; j < img->width; ++j)
		{
			uchar* p = (uchar*)img->imageData + i * img->widthStep + j;
			uchar* p2 = (uchar*)out->imageData + i * out->widthStep + j;
			int sum = *p, n = 1;
			for (int k = 0; k < 8; ++k)
			{
				int x = i+dir2[k][0];
				int y = j+dir2[k][1];
				if (law(img, x, y))
				{
					uchar* ptr = (uchar*)img->imageData + x * img->widthStep + y;
					sum += *ptr;
					++n;
				}
			}
			sum = (int)(1.0*sum / n + 0.5);
			*p2 = sum;
		}
}
//��ֵ�˲�
void medianSmooth(IplImage* img, IplImage* &out)
{
	out = cvCreateImage(cvGetSize(img), img->depth, 1);
	int dir2[8][2] = {-1, -1, -1, 1, 1, -1, 1, 1, 0, -1, 0, 1, 1, 0, -1, 0};
	for (int i = 0; i < img->height; ++i)
		for (int j = 0; j < img->width; ++j)
		{
			uchar* p = (uchar*)img->imageData + i * img->widthStep + j;
			uchar* p2 = (uchar*)out->imageData + i * out->widthStep + j;
			int n = 1;
			int s[9];
			s[0] = *p;
			for (int k = 0; k < 8; ++k)
			{
				int x = i+dir2[k][0];
				int y = j+dir2[k][1];
				if (law(img, x, y))
				{
					uchar* ptr = (uchar*)img->imageData + x * img->widthStep + y * img->nChannels;
					s[n++] = *ptr;
				}
			}
			sort(s, s+n);
			*p2 = s[n/2];
		}
}

//ungerƽ��
bool isBlack(IplImage* img, int x, int y)
{
	if (!law(img, x, y)) return false;
	uchar* p = (uchar*)img->imageData + x * img->widthStep + y * img->nChannels;
	return (*p == 0);
}
void ungerSmooth(IplImage* img, IplImage* &out)
{
	out = cvCreateImage(cvGetSize(img), img->depth, 1);
	cvCopy(img, out);

	for (int i = 0; i < img->height; ++i)
		for (int j = 0; j < img->width; ++j)
		{
			uchar* p = (uchar*)img->imageData + i * img->widthStep + j;
			uchar* p2 = (uchar*)out->imageData + i * out->widthStep + j;
			if (*p == 255)
			{
				int sum = 0;
				if (isBlack(img, i, j+1)) ++sum;
				if (isBlack(img, i-1, j)) ++sum;
				if (isBlack(img, i, j-1)) ++sum;
				if (isBlack(img, i+1, j)) ++sum;
				if (sum >= 3) *p2 = 0;
			}else
			{
				int sum1 = 0;
				if (isBlack(img, i-1, j-1)) ++sum1;
				if (isBlack(img, i-1, j)) ++sum1;
				if (isBlack(img, i, j-1)) ++sum1;
				int sum2 = 0;
				if (isBlack(img, i+1, j+1)) ++sum2;
				if (isBlack(img, i+1, j)) ++sum2;
				if (isBlack(img, i, j+1)) ++sum2;
				int sum3 = 0;
				if (isBlack(img, i, j+1)) ++sum3;
				if (isBlack(img, i-1, j+1)) ++sum3;
				if (isBlack(img, i-1, j)) ++sum3;
				int sum4 = 0;
				if (isBlack(img, i, j-1)) ++sum4;
				if (isBlack(img, i+1, j-1)) ++sum4;
				if (isBlack(img, i+1, j)) ++sum4;
				if (!(sum1 != 0 && sum2 != 0 || sum3 != 0 && sum4 != 0)) *p2 = 255;
			}
		}
}

//hilditchϸ��
int func_nc8(int *b)
{
  int n_odd[4] = {1, 3, 5, 7};
  int i, j, sum, d[10];
  
  for (i = 0; i <= 9; i++) {
    j = i;
    if (i == 9) j = 1;
    if (abs(*(b + j)) == 1) {
      d[i] = 1;
    } else {
      d[i] = 0;
    }
  }
  sum = 0;
  for (i = 0; i < 4; i++) {
    j = n_odd[i];
    sum = sum + d[j] - d[j] * d[j + 1] * d[j + 2];
  }
  return (sum);
}

void hilditch(IplImage* img)
{
	int offset[9][2] = {{0,0},{1,0},{1,-1},{0,-1},{-1,-1},
				{-1,0},{-1,1},{0,1},{1,1} }; /* offsets for neighbors */
	int n_odd[4] = { 1, 3, 5, 7 };      /* odd-number neighbors */
	int px, py;                         /* X/Y coordinates  */
	int b[9];                           /* gray levels for 9 neighbors */
	int condition[6];                   /* valid for conditions 1-6 */
	int counter;                        /* number of changing points  */
	int i, x, y, copy, sum;             /* control variable          */
	int x_size1 = img->height, y_size1 = img->width, BLACK = 0, WHITE = 255, GRAY = 128;
	/* processing starts */
	do {
		counter = 0;
		for (y = 0; y < y_size1; y++) {
			for (x = 0; x < x_size1; x++) {
			/* substitution of 9-neighbor gray values */
			for (i = 0; i < 9; i++) {
				b[i] = 0;
				px = x + offset[i][0];
				py = y + offset[i][1];
				if (px >= 0 && px < x_size1 && py >= 0 && py < y_size1)
				{
					uchar* ptr = (uchar*)img->imageData + px* img->widthStep + py;
					if (*ptr == BLACK)
					{
						b[i] = 1;
					}else if (*ptr == GRAY){
						b[i] = -1;
					}
				}
			}
			for (i = 0; i < 6; i++) {
				condition[i] = 0;
			}
			/* condition 1: figure point */
			if (b[0] == 1) condition[0] = 1;
			/* condition 2: boundary point */
			sum = 0;
			for (i = 0; i < 4; i++) {
				sum = sum + 1 - abs(b[n_odd[i]]);
			}
			if (sum >= 1) condition[1] = 1;
			/* condition 3: endpoint conservation */
			sum = 0;
			for (i = 1; i <= 8; i++) {
				sum = sum + abs(b[i]);
			}
			if (sum >= 2) condition[2] = 1;
			/* condition 4: isolated point conservation */
			sum = 0;
			for (i = 1; i <= 8; i++) {
				if (b[i] == 1) sum++;
			}
			if (sum >= 1) condition[3] = 1;
			/* condition 5: connectivity conservation */
			if (func_nc8(b) == 1) condition[4] = 1;
			/* condition 6: one-side elimination for line-width of two */
			sum = 0;
			for (i = 1; i <= 8; i++) {
				if (b[i] != -1) {
				sum++;
				} else {
				copy = b[i];
				b[i] = 0;
				if (func_nc8(b) == 1) sum++;
				b[i] = copy;
				}
			}
			if (sum == 8) condition[5] = 1;
			/* final decision */
			if (condition[0] && condition[1] && condition[2] &&
				condition[3] && condition[4] && condition[5])
			{
				uchar* ptr = (uchar*)img->imageData + x* img->widthStep + y;
				*ptr = GRAY; /* equals -1 */
				counter++;
			}
				} /* end of x */
			} /* end of y */
			if (counter != 0) {
				for (y = 0; y < y_size1; y++) {
			for (x = 0; x < x_size1; x++) {
				uchar* ptr = (uchar*)img->imageData + x* img->widthStep + y;
				if (*ptr == GRAY) *ptr = WHITE;
			}
			}
		}
	} while (counter != 0);
}

//dpȥ��
void antiLine(IplImage* img)
{
	int** map = new int*[img->height];
	for (int i = 0; i < img->height; ++i)
		map[i] = new int[img->width];
	for (int i = 0; i < img->height; ++i)
	{
		uchar* ptr = (uchar*)img->imageData + i* img->widthStep + 0;
		if (*ptr == 0) map[i][0] = img->height;
		else map[i][0] = 0;
	}
	for (int y = 1; y < img->width; ++y)
		for(int x = 0; x < img->height; ++x)
		{
			uchar* ptr = (uchar*)img->imageData + x* img->widthStep + y;
			if (*ptr == 0)
			{
				int max = map[0][y-1] + img->height - (x-0);// maxk = 0;
				for (int k = 1; k < img->height; ++k)
				{
					int tmp = map[k][y-1] + img->height - abs(x - k);
					if (tmp > max)
					{
						max = tmp;
						//maxk = k;
					}
				}
				map[x][y] = max;
			}else map[x][y] = 0;
		}
	for (int y = 0; y < img->width; ++y)
	{
		int maxx = 0, max = 0;
		for(int x = 0; x < img->height; ++x)
			if(map[x][y] > max)
			{
				max = map[x][y];
				maxx = x;
			}
		uchar* ptr = (uchar*)img->imageData + maxx* img->widthStep + y;
		*ptr = 255;
	}
	/*for(int x = 0; x < img->height; ++x)
	{
		for (int y = 0; y < img->width; ++y)
			cout << map[x][y]<<"  ";
		cout <<endl;
	}*/
}

//���
void fillNull(IplImage* img)
{
	for (int i = 0; i < img->height; ++i)
		for (int j = 0; j < img->width; ++j)
			if (law(img, i-1, j) && law(img, i+1, j))
			{
				uchar* ptr = (uchar*)img->imageData + i* img->widthStep + j;
				uchar* ptr1 = (uchar*)img->imageData + (i-1)* img->widthStep + j;
				uchar* ptr2 = (uchar*)img->imageData + (i+1)* img->widthStep + j;
				if (*ptr1 == 0 && *ptr2 == 0)
					*ptr = 0;
			}
}

void biliCaptchaProcess()
{
	for (int i = 1; i <= 300; ++i)
	{
		char s[50];
		sprintf(s, "bb\\Image%03d.png", i);
		img = cvLoadImage(s);
		img2 = cvCreateImage(cvGetSize(img), img->depth, 1);
		cvCvtColor(img,img2,CV_RGB2GRAY);
		img3 = cvCreateImage(cvGetSize(img), img->depth, 1);
		int thr = otsu(img2);
		cvThreshold(img2, img3, thr, 255, CV_THRESH_BINARY);
		//����ǰ��־ͷ�ɫ
		int blackNum=0, whiteNum=0;
		for (int i = 0; i < img3->height; ++i)
			for (int j = 0; j < img3->width; ++j)
			{
				uchar* pin = (uchar*)img3->imageData + i * img3->widthStep + j;
				if ((*pin) == 0)  ++blackNum;
				else ++whiteNum;
			}
		if (blackNum > whiteNum) cvNot(img3, img3);
		cvCopy(img3, img2);
		antiNoise(img2, 10);
		medianSmooth(img2, img3);
		antiNoise(img3, 10);
		ungerSmooth(img3, img2);
		antiNoise(img2, 10);
		sprintf(s, "bbed\\Image%03d.png", i);
		cvSaveImage(s, img2);

		cvReleaseImage(&img);
		cvReleaseImage(&img2);
		cvReleaseImage(&img3);
	}
}

void capt()
{
	FILE* fout = fopen("out1.txt", "w");

	for (int i = 1; i <= 300; ++i)
	{
		char s[50];
		sprintf(s, "bbed\\Image%03d.png", i);
		img = cvLoadImage(s);

		tesseract::TessBaseAPI tess;
		tess.Init(NULL, "eng");
		IplImage* imgh = img;
		tess.SetImage((uchar*)imgh->imageData, imgh->width, imgh->height, imgh->nChannels, imgh->widthStep);
		tess.SetPageSegMode(tesseract::PSM_SINGLE_WORD);
		tess.SetVariable("tessedit_char_whitelist", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
		char* out = tess.GetUTF8Text();
		cout << i<<":"<<out;
		fprintf(fout,"%d:%s", i, out);
	}
	fclose(fout);
}

void tyPreprocess(char* in, char* out)
{
	img = cvLoadImage(in);
	//cvNamedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
	//cvShowImage("ԭͼ", img);
	//system("pause");
	img2 = cvCreateImage(cvGetSize(img), img->depth, 1);
	cvCvtColor(img,img2,CV_RGB2GRAY);

	//cvNamedWindow("�ҶȻ�", CV_WINDOW_AUTOSIZE);
	//cvShowImage("�ҶȻ�", img2);
	//- -����ȥ�߿�
	int thickness = 1;
	cvRectangle( img2, cvPoint(0, 0), cvPoint(img2->width - 1, img2->height - 1), CV_RGB(255,255,255), thickness);

	//��ֵ��
	img3 = cvCreateImage(cvGetSize(img), img->depth, 1);
	//OTSU
	int thr = otsu(img2);
	printf("threshold: %d\n", thr);
	cvThreshold(img2, img3, thr, 255, CV_THRESH_BINARY);

	//cvNamedWindow("OTSU��ֵ��", CV_WINDOW_AUTOSIZE);
	//cvShowImage("OTSU��ֵ��", img3);

	//����ǰ��־ͷ�ɫ
	int blackNum=0, whiteNum=0;
	for (int i = 0; i < img3->height; ++i)
		for (int j = 0; j < img3->width; ++j)
		{
			uchar* pin = (uchar*)img3->imageData + i * img3->widthStep + j;
			if ((*pin) == 0)  ++blackNum;
			else ++whiteNum;
		}
	if (blackNum > whiteNum) cvNot(img3, img3);

	//cvNamedWindow("��ɫ��", CV_WINDOW_AUTOSIZE);
	//cvShowImage("��ɫ��", img3);

	//- -����ȥ�߿�
	//int thickness = 1;
	cvRectangle( img3, cvPoint(0, 0), cvPoint(img3->width - 1, img3->height - 1), CV_RGB(255,255,255), thickness);

	cvCopy(img3, img2);
	antiNoise(img2, 10);
	medianSmooth(img2, img3);
	antiNoise(img3, 10);
	ungerSmooth(img3, img2);
	antiNoise(img2, 10);
	//cvNamedWindow("final", CV_WINDOW_AUTOSIZE);
	//cvShowImage("final", img2);
	cvSaveImage(out, img2);
}

char* tyKnow(char* in)
{
	img = cvLoadImage(in);
	tesseract::TessBaseAPI tess;
	tess.Init(NULL, "eng");
	IplImage* imgh = img;
	tess.SetImage((uchar*)imgh->imageData, imgh->width, imgh->height, imgh->nChannels, imgh->widthStep);
	tess.SetPageSegMode(tesseract::PSM_SINGLE_WORD);
	tess.SetVariable("tessedit_char_whitelist", "0123456789abcdefghijklmnopqrstuvwsyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	char* out = tess.GetUTF8Text();
	return out;
}

void tyTinyPreprocess(char* in, char* out)
{
	img = cvLoadImage(in);

	img2 = cvCreateImage(cvGetSize(img), img->depth, 1);
	cvCvtColor(img,img2,CV_RGB2GRAY);
	//- -����ȥ�߿�
	int thickness = 1;
	cvRectangle( img2, cvPoint(0, 0), cvPoint(img2->width - 1, img2->height - 1), CV_RGB(255,255,255), thickness);

	//��ֵ��
	img3 = cvCreateImage(cvGetSize(img), img->depth, 1);
	//OTSU
	int thr = otsu(img2);
	//printf("threshold: %d\n", thr);
	cvThreshold(img2, img3, thr, 255, CV_THRESH_BINARY);

	//����ǰ��־ͷ�ɫ
	int blackNum=0, whiteNum=0;
	for (int i = 0; i < img3->height; ++i)
		for (int j = 0; j < img3->width; ++j)
		{
			uchar* pin = (uchar*)img3->imageData + i * img3->widthStep + j;
			if ((*pin) == 0)  ++blackNum;
			else ++whiteNum;
		}
	if (blackNum > whiteNum) cvNot(img3, img3);
	//- -����ȥ�߿�
	//int thickness = 1;
	cvRectangle( img3, cvPoint(0, 0), cvPoint(img3->width - 1, img3->height - 1), CV_RGB(255,255,255), thickness);

	cvCopy(img3, img2);
	antiNoise(img2, 6);
	ungerSmooth(img2, img3);
	antiNoise(img3, 3);
	fillNull(img3);
	cvSaveImage(out, img3);
}

void tyLinePreprocess(char* in, char* out)
{
	img = cvLoadImage(in);
	//cvNamedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
	//cvShowImage("ԭͼ", img);
	//system("pause");
	img2 = cvCreateImage(cvGetSize(img), img->depth, 1);
	cvCvtColor(img,img2,CV_RGB2GRAY);

	//cvNamedWindow("�ҶȻ�", CV_WINDOW_AUTOSIZE);
	//cvShowImage("�ҶȻ�", img2);
	//- -����ȥ�߿�
	int thickness = 1;
	cvRectangle( img2, cvPoint(0, 0), cvPoint(img2->width - 1, img2->height - 1), CV_RGB(255,255,255), thickness);

	//��ֵ��
	img3 = cvCreateImage(cvGetSize(img), img->depth, 1);
	//OTSU
	int thr = otsu(img2);
	//printf("threshold: %d\n", thr);
	cvThreshold(img2, img3, thr, 255, CV_THRESH_BINARY);

	//cvNamedWindow("OTSU��ֵ��", CV_WINDOW_AUTOSIZE);
	//cvShowImage("OTSU��ֵ��", img3);

	//����ǰ��־ͷ�ɫ
	int blackNum=0, whiteNum=0;
	for (int i = 0; i < img3->height; ++i)
		for (int j = 0; j < img3->width; ++j)
		{
			uchar* pin = (uchar*)img3->imageData + i * img3->widthStep + j;
			if ((*pin) == 0)  ++blackNum;
			else ++whiteNum;
		}
	if (blackNum > whiteNum) cvNot(img3, img3);

	//cvNamedWindow("��ɫ��", CV_WINDOW_AUTOSIZE);
	//cvShowImage("��ɫ��", img3);

	//- -����ȥ�߿�
	//int thickness = 1;
	cvRectangle( img3, cvPoint(0, 0), cvPoint(img3->width - 1, img3->height - 1), CV_RGB(255,255,255), thickness);

	cvCopy(img3, img2);
	antiNoise(img2, 10);
	//medianSmooth(img2, img3);
	//antiNoise(img3, 10);
	antiLine(img2);
	fillNull(img2);
	//ungerSmooth(img2, img3);
	//antiNoise(img3, 10);
	//cvNamedWindow("final", CV_WINDOW_AUTOSIZE);
	//cvShowImage("final", img2);
	cvSaveImage(out, img2);
}


int _tmain(int argc, _TCHAR* argv[])
{
	//biliCaptchaProcess();
	//capt();
	//tyPreprocess("007.png", "tmp.png");
	//tyTinyPreprocess("007.png", "tmp.png");
	tyLinePreprocess("Image001.jpg", "tmp.png");
	cout <<tyKnow("tmp.png")<<endl;
	system("pause");
	return 0;

	img = cvLoadImage("Image006.png");
	cvNamedWindow("ԭͼ", CV_WINDOW_AUTOSIZE);
	cvShowImage("ԭͼ", img);
	//cvWaitKey(0);
	//�ҶȻ�
	img2 = cvCreateImage(cvGetSize(img), img->depth, 1);
	//printf("img->nChannels:%d", img->nChannels);

	cvCvtColor(img,img2,CV_RGB2GRAY);

	cvNamedWindow("�ҶȻ�", CV_WINDOW_AUTOSIZE);
	cvShowImage("�ҶȻ�", img2);

	//�ҶȻ�Ч���Ա�
	//grayShow();

	////�Ҷ�����??
	//;
	////ֱ��ͼ���⻯..Ч������
	////cvEqualizeHist(img2, img2);

	//ȥ�߿�
	//int thickness = 1;
	//cvRectangle( img3, cvPoint(0, 0), cvPoint(img3->width - 1, img3->height - 1), CV_RGB(255,255,255), thickness);

	//clearFrameStarter(img2);

	//cvNamedWindow("ȥ�߿��", CV_WINDOW_AUTOSIZE);
	//cvShowImage("ȥ�߿��", img2);

	//- -����ȥ�߿�
	int thickness = 1;
	cvRectangle( img2, cvPoint(0, 0), cvPoint(img2->width - 1, img2->height - 1), CV_RGB(255,255,255), thickness);

	//��ֵ��
	img3 = cvCreateImage(cvGetSize(img), img->depth, 1);
	//OTSU
	//cvThreshold(img2, img3, 300 , 255,   CV_THRESH_OTSU | CV_THRESH_BINARY);
	int thr = otsu(img2);
	printf("threshold: %d\n", thr);
	cvThreshold(img2, img3, thr, 255, CV_THRESH_BINARY);

	cvNamedWindow("OTSU��ֵ��", CV_WINDOW_AUTOSIZE);
	cvShowImage("OTSU��ֵ��", img3);

	//������ѡ��ֵ
	//img4 = cvCreateImage(cvGetSize(img), img->depth, 1);
	//cvNamedWindow("threshold", CV_WINDOW_AUTOSIZE);
	//cvCreateTrackbar("T", "threshold", 0, 255, onchange);
	//cvShowImage("threshold", img4);

	//�̶���ֵ120
	//img5 = cvCreateImage(cvGetSize(img), img->depth, 1);
	//cvThreshold(img2, img5, 120, 255, CV_THRESH_BINARY);
	//cvNamedWindow("Example5", 0);
	//cvCreateTrackbar("tcbar2", "Example5", NULL, 255, onchange2);
	//cvShowImage("Example5", img5);

	//cvNamedWindow("Example3", CV_WINDOW_AUTOSIZE);
	//cvShowImage("Example3", img3);

	//����ǰ��־ͷ�ɫ
	int blackNum=0, whiteNum=0;
	for (int i = 0; i < img3->height; ++i)
		for (int j = 0; j < img3->width; ++j)
		{
			uchar* pin = (uchar*)img3->imageData + i * img3->widthStep + j;
			if ((*pin) == 0)  ++blackNum;
			else ++whiteNum;
		}
	if (blackNum > whiteNum) cvNot(img3, img3);

	cvNamedWindow("��ɫ��", CV_WINDOW_AUTOSIZE);
	cvShowImage("��ɫ��", img3);

	//- -����ȥ�߿�
	//int thickness = 1;
	cvRectangle( img3, cvPoint(0, 0), cvPoint(img3->width - 1, img3->height - 1), CV_RGB(255,255,255), thickness);

	//��ֵ�˲�ȥ����,��С�Բ�ͬ��֤�벻һ����006.png��
	//img6 = cvCreateImage(cvGetSize(img), img->depth, 1);
	//cvSmooth(img3, img6, CV_MEDIAN, 3);
	////cvSmooth(img3, img6, CV_BLUR, 3, 3);
	//cvNamedWindow("��ֵ�˲�", CV_WINDOW_AUTOSIZE);
	//cvCreateTrackbar("tcbar3", "��ֵ�˲�", NULL, 100, onchange3);
	//cvShowImage("��ֵ�˲�", img6);

	//��ֵ�˲�2
	//img6 = cvCreateImage(cvGetSize(img), img->depth, 1);
	//cvCopy(img3, img6);
	antiNoise(img3, 10);
	medianSmooth(img3, img6);
	cvNamedWindow("��ͨȥ�����ֵ�˲�", CV_WINDOW_AUTOSIZE);
	cvShowImage("��ͨȥ�����ֵ�˲�", img6);

	//antiNoise(img6, 10);
	//cvNamedWindow("�˲�����ͨ��ȥ��", CV_WINDOW_AUTOSIZE);
	//cvShowImage("�˲�����ͨ��ȥ��", img6);

	//unger
	ungerSmooth(img6, img3);
	cvNamedWindow("unger�˲�", CV_WINDOW_AUTOSIZE);
	cvShowImage("unger�˲�", img3);

	//��ͨ��ȥ��
	//antiNoise(img3, 10);
	//cvNamedWindow("��ͨ��ȥ��", CV_WINDOW_AUTOSIZE);
	//cvShowImage("��ͨ��ȥ��", img3);

	//cvSmooth(img3, img6, CV_MEDIAN, 3, 3);
	////cvSmooth(img3, img6, CV_BLUR, 3, 3);
	//cvNamedWindow("ȥ����˲�", CV_WINDOW_AUTOSIZE);
	//cvCreateTrackbar("tcbar3", "ȥ����˲�", NULL, 100, onchange3);
	//cvShowImage("ȥ����˲�", img6);

	//ƽ��
	
	//hilditch(img3);
	//cvNamedWindow("img", CV_WINDOW_AUTOSIZE);
	//cvShowImage("img", img3);

	//antiLine(img3);
	//cvNamedWindow("dp", CV_WINDOW_AUTOSIZE);
	//cvShowImage("dp", img3);

	//��ͨ��ȥ��again
	//antiNoise(img3, 3);
	//cvNamedWindow("final", CV_WINDOW_AUTOSIZE);
	//cvShowImage("final", img3);
	//http://weibo.cn/interface/f/ttt/captcha/show.php?cpt=2_2b1b798ec3a2ca22
	//ocr
	tesseract::TessBaseAPI tess;
    tess.Init(NULL, "eng");
	IplImage* imgh = img3;
	tess.SetImage((uchar*)imgh->imageData, imgh->width, imgh->height, imgh->nChannels, imgh->widthStep);
	tess.SetPageSegMode(tesseract::PSM_SINGLE_WORD);
	tess.SetVariable("tessedit_char_whitelist", "0123456789abcdefghijklmnopqrstuvwsyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	//int starty = 0;
	//bool start = false;
	//for (int y = 0; y < imgh->width; ++y)
	//{
	//	bool hasblack = false;
	//	for(int x = 0; x < imgh->height; ++x)
	//	{
	//		uchar* ptr = (uchar*)imgh->imageData + x* imgh->widthStep + y;
	//		if (!start && *ptr == 0)
	//		{
	//			start = true;
	//			starty = y;
	//			hasblack = true;
	//			break;
	//		}else if (start && *ptr == 0)
	//		{
	//			hasblack = true;
	//			break;
	//		}
	//	}
	//	if (start && !hasblack)
	//	{
	//		
	//		cout << starty << "~~"<<y <<endl;
	//		if (starty != y)
	//		{
	//			tess.SetRectangle(starty, 0, y - starty, imgh->height);
	//			tess.Recognize(0);
	//			char* out = tess.GetUTF8Text();
	//			cout << out << endl;
	//		}
	//		start = false;
	//	}
	//}
	//if (start)
	//{
	//	
	//}


	//tess.SetImage((uchar*)imgh->imageData, imgh->width, imgh->height, imgh->nChannels, imgh->widthStep);
	//tess.SetPageSegMode(tesseract::PSM_SINGLE_WORD);
	//tess.SetVariable("tessedit_char_whitelist", "0123456789abcdefghijklmnopqrstuvwsyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	//tess.Recognize(0);
    char* out = tess.GetUTF8Text();
    cout << out << endl;
	cout << "over" <<endl;
	//int *gg = tess.AllWordConfidences();
	//while (*gg != '\0')
	//{
	//	printf("%d\n",*gg);
	//	gg ++ ;
	//}


	////��ʴ���Ϳ��տ���Ч��=��=
	//IplConvKernel* kn = cvCreateStructuringElementEx(2, 2, 1, 1, CV_SHAPE_CROSS);
	////img7[0] = cvCreateImage(cvGetSize(img), img->depth, 1);
	////cvNot(img3, img7[0]);
	////cvErode(img7[0], img7[0], kn, 2);//fushi
	////cvNot(img7[0], img7[0]);
	////cvNamedWindow("Example7[0]", CV_WINDOW_AUTOSIZE);
	////cvShowImage("Example7[0]", img7[0]);

	////img7[1] = cvCreateImage(cvGetSize(img), img->depth, 1);
	////cvDilate(img3, img7[1], kn);//pengzhang
	////cvNamedWindow("Example7[1]", CV_WINDOW_AUTOSIZE);
	////cvShowImage("Example7[1]", img7[1]);
	////6
	//img7[2] = cvCreateImage(cvGetSize(img), img->depth, 1);
	//cvNot(img3, img7[2]);
	//cvMorphologyEx(img7[2], img7[2], NULL, kn, CV_MOP_OPEN, 2);//kai
	//cvNot(img7[2], img7[2]);
	//cvNamedWindow("Example7[2]", CV_WINDOW_AUTOSIZE);
	//cvShowImage("Example7[2]", img7[2]);
	//////6
	////img7[3] = cvCreateImage(cvGetSize(img), img->depth, 1);
	////cvMorphologyEx(img6, img7[3], NULL, kn, CV_MOP_CLOSE);//bi
	////cvNamedWindow("Example7[3]", CV_WINDOW_AUTOSIZE);
	////cvShowImage("Example7[3]", img7[3]);

	////hough�任�����
	//img7[4] = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);  //������ͨ��ͼ��  
 //   CvMemStorage* storage = cvCreateMemStorage(0);  
 //   CvSeq* lines = 0;
 //   //cvCanny( src, dst, 50, 100, 3);  //�������б�Ե��⣬����ԻҶ�ͼ��ʾ��ֻ�б�Ե)
 //   cvCvtColor( img3, img7[4], CV_GRAY2BGR); //ɫ�ʿռ�ת������dstת��������һ��ɫ�ʿռ伴3ͨ��ͼ��
	//lines = cvHoughLines2(img3, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI/180, 15, 21, 4); //ֱ�ӵõ�ֱ������
 //   for(int i = 0; i < lines ->total; i++)//lines�洢����ֱ��
 //   {
 //       CvPoint* line = ( CvPoint* )cvGetSeqElem(lines, i);//lines��������洢�������ص�����  
 //       cvLine( img7[4], line[0], line[1], CV_RGB( 0, 255, 0));//���ҵ���ֱ�߱��Ϊlvɫ  
 //       //color_dst����ͨ��ͼ��������ֱ��ͼ��
 //   }
	//cvNamedWindow("Example7[4]", 1);
	//cvCreateTrackbar("tcbar741", "Example7[4]", &e1, 100, onchange74);
	//cvCreateTrackbar("tcbar742", "Example7[4]", &e2, 100, onchange74);
	//cvCreateTrackbar("tcbar743", "Example7[4]", &e3, 100, onchange74);
	//cvShowImage("Example7[4]", img7[4]);

	//��ͨ�Էָ�  ����������
	//CvMemStorage* sto = cvCreateMemStorage(0);
	//IplImage* imgtmp = cvCloneImage(img6);
	//CvContourScanner scanner
	//	= cvStartFindContours(imgtmp,sto,sizeof(CvContour),CV_RETR_CCOMP,CV_CHAIN_APPROX_NONE,cvPoint(0,0));//img6����- -
	////��ʼ����������
 //   CvRect rect;
	//CvSeq* contour = NULL;
	//double minarea = 10;
 //   double tmparea = 0;
	//IplImage* img8 = cvCreateImage(cvGetSize(img), img->depth, 1);
	//cvCopy(img6, img8, NULL);
 //   while (contour=cvFindNextContour(scanner))
 //   {
 //       tmparea = fabs(cvContourArea(contour));
	//	printf("%f\n", tmparea);
 //       rect = cvBoundingRect(contour,0);
 //       if (tmparea < minarea/*||tmparea>4900*/)
 //       {
 //       //����ͨ������ĵ�Ϊ��ɫʱ�����������С���ð�ɫ�������
 //           uchar* pp=(uchar*)(img8->imageData+img8->widthStep*rect.y+rect.x);//(uchar*)(img8->imageData + img8->widthStep*(rect.y+rect.height/2)+rect.x+rect.width/2);
 //           if (pp[0]==0)
 //           {
 //               cvDrawContours(img8, contour, cvScalarAll(255), cvScalarAll(0), 0, CV_FILLED);
 //           }
	//	  }
 //       }
	//cvNamedWindow("Example8", CV_WINDOW_AUTOSIZE);
	//cvShowImage("Example8", img8);


	cvWaitKey(0);
	//cvReleaseImage(&img);
	//cvDestroyWindow("Example1");
	//cvDestroyWindow("Example2");
}
