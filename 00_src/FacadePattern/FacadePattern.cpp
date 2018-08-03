#include <iostream>
class ImageWork 
{
public:

};
class Image
{

};
class ImageLoad
{

};
class ImageResult
{

};
class FacadeHandler
{
public:
	void DoWork(const ImageWork & image, ImageResult & result)
	{
		//....
		m_Image = ImageLoad(image.m_szName);
		//명암 변경
		result = ImageWork.DoWork(m_Image);
	}
private:
	Image m_Image;
};


int main()
{
	ImageWork image("aaa.bmp");
	FacadeHandler work;
	ImageResult result;
	work.DoWork(image, result);
	return 0;
}