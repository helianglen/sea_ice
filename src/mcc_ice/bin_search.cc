
//uses a binary search to search an ordered list:
template <class dt>
long bin_search (dt *list, long n, dt value, long last_ind) {

//+****************************************************************************
//		BIN_SEARCH
//*****************************************************************************
//
// usage:	index=bin_search(list, n, value, last_ind)
//
// purpose:	Performs a binary search on an ordered list of values.  Returns
//		the subscript of the smallest array element closest.
//
// parameters:	list	An array of values sorted in ascending order.
//
//		n	Number of elements in the list.
//
//		value	The value to search for.
//
//		last_ind	Last value found.  Set to -1 to tell the routine to bracket
//			the entire list right from the start.
//
// author:	Peter Mills (peter.mills@nrl.navy.mil)
//
// history:	First formally documented 2001-12-07 while making some routine
//		improvements.
//		-2002-02-11	PM added the last keyword
//
//		2003-2-25 PM: converted to a C++ template and cleaned up the code a bit
//		2003-3-09 PM: split into two routines;  changed behaviour so
//			that a value higher than the highest returns the
//			largest subscript instead of the number of elements.
//			
//		2003-12-13 PM: corrected bug that made it return a false
//			value if the search value was one step ahead of the last
//			Also made a small change to make it more efficient.
//
//		2004-1-27 PM: cleaned up the logic some more...
//
//-******************************************************************************

  long first, last, mid;		//indices to bracket list
  long step;
  double frac;

  last=n-1;
  first=0;

  //check to see if the value is either first or last in the list:

  if (value == list[last]) {
    return last;
  } else if (value > list[last]) {
    return last;
  } else if (value == list[first]) {
    return first;
  } else if (value < list [first]) {
    return -1;

  //if last is set, search first in the vicinity of that
  //index, expanding outward from there:
  } else if (last_ind >= 0 && last_ind < n) {
    if (list[last_ind]==value) {
      return last_ind;
    } else if (value < list[last_ind]) {
      first=last_ind;
      last=last_ind;
      step=-1;
      do {
        last=first;
        first=first+step;
        if (first<0) {
	  first=0;
	  break;
	}
        if (value == list[first]) return first;
        step=step*2;
      } while (value < list[first]);
    } else {
      first=last_ind;
      last=last_ind;
      step=1;
      do {
        first=last;
        last=last+step;
        if (last >= n) {
	  last=n-1;
	  break;
	}
        if (value == list[last]) return last;
        step=step*2;
      } while (value > list[last]);
    }
  }


  //the actual binary search (not very big is it??)
  while (last-first > 1) {
    mid=(last+first)/2;
//    print, time_string(value), time_string list[mid]), comp
    if (value == list[mid]) return mid;
    if (value > list[mid]) {
      first=mid;
    } else {
      last=mid;
    }
  }

  return first;

}

//uses a binary search to search an ordered list:
template <class dt>
double interpolate (dt *list, long n, dt value, long last_ind) {

//+****************************************************************************
//		INTERPOLATE
//*****************************************************************************
//
// usage:	index=interpolate(list, n, value, last_ind)
//
// purpose:	Performs a binary search on an ordered list of values.  Returns
//		the subscript of the smallest array element closest to the value
//		with the decimal part set to the fractional distance of the value
//		between the two nearest elements (smaller and larger) of the list.
//
// parameters:	list	An array of values sorted in ascending order.
//
//		n	Number of elements in the list.
//
//		value	The value to search for.
//
//		last_ind	Last value found.  Set to -1 to tell the routine to bracket
//			the entire list right from the start.
//
// author:	Peter Mills (peter.mills@nrl.navy.mil)
//
// history:	First formally documented 2001-12-07 while making some routine
//		improvements.
//		2002-02-11 PM:	added the last keyword
//
//		2003-2-25 PM: 	converted to a C++ template and cleaned up the code a bit
//		2003-3-09 PM: 	split into two routines;  changed behaviour so
//			that a value higher than the highest returns the
//			largest subscript instead of the number of elements.
//
//		2003-12-04 PM:	changed routine to extrapolate in the event
//			of the value being outside the range
//
//		2003-12-13 PM: made same changes to this as to bin_search, above
//
//		2004-1-27 PM: cleaned up the logic some more...
//
//-******************************************************************************

  long first, last, mid;		//indices to bracket list
  long step;
  double frac;

  last=n-1;
  first=0;

  //check to see if the value is either first or last in the list:

  if (value == list[last]) {
    return (double) last;
  } else if (value > list[last]) {
    if (n==1) return (double) last;
    //do the interpolation (get the fractional component of the index):
    frac=((double) value-(double) list[last])/
  		((double) list[last]-(double) list[last-1]);
    return (double) last + frac;
  } else if (value == list[first]) {
    return (double) first;
  } else if (value < list [first]) {
    if (n==1) return (double) -1;
  //do the interpolation (get the fractional component of the index):
    frac=((double) value-(double) list[first])/
  		((double) list[first+1]-(double) list[first]);
    return (double) first + frac;
  //if last is set, search first in the vicinity of that
  //index, expanding outward from there:
  } else if (last_ind >= 0 && last_ind < n) {
    if (list[last_ind]==value) {
      return (double) last_ind;
    } else if (value < list[last_ind]) {
      first=last_ind;
      last=last_ind;
      step=-1;
      do {
        last=first;
        first=first+step;
        if (first<0) {
	  first=0;
	  break;
	}
        if (value == list[first]) return (double) first;
        step=step*2;
      } while (value < list[first]);
    } else {
      first=last_ind;
      last=last_ind;
      step=1;
      do {
        first=last;
        last=last+step;
        if (last >= n) {
	  last=n-1;
	  break;
	}
        if (value == list[last]) return (double) last;
        step=step*2;
      } while (value > list[last]);
    }
  }


  //the actual binary search (not very big is it??)
  while (last-first > 1) {
    mid=(last+first)/2;
//    print, time_string(value), time_string list[mid]), comp
    if (value == list[mid]) return (double) mid;
    if (value > list[mid]) {
      first=mid;
    } else {
      last=mid;
    }
  }

  //do the interpolation (get the fractional component of the index):
  frac=((double) value-(double) list[first])/
  		((double) list[first+1]-(double) list[first]);
  return (double) first + frac;

}

template long bin_search<double>(double *, long, double, long);
template double interpolate<double>(double *, long, double, long);

