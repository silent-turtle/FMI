#include "Bitmap.h"

#include <iostream>

const size_t MAX_SIZE = 100000; 

void cropUpperRows(unsigned int arr[MAX_SIZE], size_t& width, size_t & height, size_t colour);
void cropLowerRows(unsigned int arr[MAX_SIZE], size_t& width, size_t & height, size_t colour);
void cropLeftmostCols(unsigned int arr[MAX_SIZE], size_t & width, size_t height, size_t colour);
void cropRightmostCols(unsigned int arr[MAX_SIZE], size_t & width, size_t height, size_t colour);

int main()
{
	unsigned int width, height, image[MAX_SIZE], colour;
	int rval;

	rval = LoadBitmap("test.bmp", image, MAX_SIZE, width, height);

	if (rval != ALL_OK)
	{
		std::cerr << "Cannot load image data from test.bmp! Error code " << rval << "\n";
		return 1;
	}

	std::cin >> colour;

	cropUpperRows(image, width, height, colour);
	cropLowerRows(image, width, height, colour);
	cropLeftmostCols(image, width, height, colour);
	cropRightmostCols(image, width, height, colour);
	
	rval = SaveBitmap("test_new.bmp", image, width, height);
	
	if (rval != ALL_OK)
	{
		std::cerr << "Cannot save image data to test_new.bmp! Error code " << rval << "\n";
		return 2;
	}

    return 0;
}


void cropUpperRows(unsigned int arr[MAX_SIZE], size_t& width, size_t & height, size_t colour)
{
	unsigned int elem_cnt = width*height, cnt = 0;
	bool hasSameColour = true;
	for (cnt; cnt < width; ++cnt) //checks if the first row has an element with a different colour
	{
		if (arr[cnt] != colour) hasSameColour = false;
	}
	while (hasSameColour)
	{
		for (cnt = 0; cnt < width; ++cnt) //checks if the next row has an element with a different colour
		{
			if (arr[width+cnt] != colour) hasSameColour = false;
		}
		for (cnt = 0; cnt < width; ++cnt) //inner loop removes first element and outter loop repeats the inner one cnt times
		{
			for (unsigned i = 0; i < elem_cnt; ++i)
			{
				arr[i] = arr[i + 1];
			}
		--elem_cnt;
		}
		height = elem_cnt / width;
	}
	
}

void cropLowerRows(unsigned int arr[MAX_SIZE], size_t& width, size_t & height, size_t colour)
{
	unsigned int elem_cnt = width*height;

	for (unsigned i = elem_cnt-1; i > 0 && arr[i] == colour; --i)
	{
		--elem_cnt;
		height = elem_cnt / width;
	}
}

void cropLeftmostCols(unsigned int arr[MAX_SIZE], size_t & width, size_t height, size_t colour)
{
	bool hasSameColour = true;
	unsigned int elem_cnt = width*height, cnt = 0;
	{
		for (unsigned k = 0; k < width && hasSameColour; ++k) //checks the number of collums with the same colour
		{
		    for (unsigned i = 0; i < height; ++i)
		    {
			     if (arr[i*width + k] != colour) hasSameColour = false;
			}
		    
			if(hasSameColour) ++cnt;
		}

		for (unsigned int i = 0; i < cnt; i++)
		{
			for(unsigned int j = 0; j < elem_cnt; ++j)
			{
				arr[j] = arr[j + 1];
			}
		}
	}
}

void cropRightmostCols(unsigned int arr[MAX_SIZE], size_t & width, size_t height, size_t colour)
{
	
	bool hasSameColour = true;
	unsigned int elem_cnt = width*height, ColumnCheck = width - 1, ColumnCheckBorder = width - 2, CurrentColumn = width - 1, CurrentColumnBorder = width - 2;
		
	for (ColumnCheck; ColumnCheck > ColumnCheckBorder; --ColumnCheck) //checks if the last column has elements with different colours
		{
			for (unsigned i = 0; i < height; ++i)
			{
				if (arr[i*width + ColumnCheck] != colour) hasSameColour = false;
			}
		}
		--ColumnCheckBorder;

		while (hasSameColour)
		{
			for (ColumnCheck; ColumnCheck > ColumnCheckBorder; --ColumnCheck) //checks if the previous column has different colours; k is width - 2 in the beginning of the loop
			{
				for (unsigned i = 0; i < height; ++i)
				{
					if (arr[i*width + ColumnCheck] != colour) hasSameColour = false;
				}
			}
			--ColumnCheckBorder;
			for (CurrentColumn; CurrentColumn > CurrentColumnBorder; --CurrentColumn)//this checks that it's working on only one column, n is width - 1 in the beginning of the loop
			{
				for (unsigned j = 0, m = width - 1; j < height; ++j, --m)
				{
					for (unsigned i = j*width + m; i < elem_cnt; ++i)//it takes the last element of each row and deletes it one by one
					{
						arr[i] = arr[i + 1];
					}
					--elem_cnt;
				}
				width = elem_cnt/height;
			}
			--CurrentColumnBorder;
		}
}
