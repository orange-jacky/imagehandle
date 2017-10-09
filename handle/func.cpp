#include "func.h"

namespace ImageHandle{
	
	Mat argsort(InputArray _src, bool ascending)
	{
	    Mat src = _src.getMat();
	    if (src.rows != 1 && src.cols != 1) {
	        string error_message = "Wrong shape of input matrix! Expected a matrix with one row or column.";
	        CV_Error(CV_StsBadArg, error_message);
	    }
	    int flags = CV_SORT_EVERY_ROW+(ascending ? CV_SORT_ASCENDING : CV_SORT_DESCENDING);
	    Mat sorted_indices;
	    sortIdx(src.reshape(1,1),sorted_indices,flags);
	    return sorted_indices;
	}
}