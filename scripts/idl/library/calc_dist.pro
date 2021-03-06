@traj_utils

function distance, lon1, lat1, lon2, lat2

;+*************************************************************************
;		DISTANCE
;**************************************************************************
;
; usage:	d=distance(v1, v2)
;
; purpose:	Returns the approximate distance (correct in the limit as 
;		it approaches 0) between two points defined in a spherical 
;		polar coords with constant radius.  For the poles, converts 
;		to a locally Cartesian system.
;
; parameters:	v1		The first vector.  Should be a two element vector
;				containing longitude and latitude respectively.
;
;		v2		The second vector in the same format as the first.
;
; side effects: if one side is a vector, makes the other side a vector as well
;
; history:	Formally documented, 2002-02-14 Peter Mills (peter.mills@nrl.navy.mil)
;		2009-6-06 PM vector operations...  wheeee!  IDL is great!
;
;-**************************************************************************

  mperdeg=40000000./360
  latthresh=87.5

  n1=n_elements(lon1)
  n2=n_elements(lon2)
  n=max([n1, n2])
  if n gt 1 then begin
    if n1 eq 1 then begin
      lon1=replicate(lon1, n)
      lat1=replicate(lat1, n)
    endif
    if n2 eq 1 then begin
      lon2=replicate(lon2, n)
      lat2=replicate(lat2, n)
    endif
  endif

  ind=where(abs(lat1) ge latthresh or abs(lat2) ge latthresh, complement=ind2, ncompl=cnt2, cnt)

  r=fltarr(n)

  if cnt gt 0 then begin
  ;if points are very close to the pole, use a local cartesian
  ;system calculate the distance:
    rearth=20000000/!pi
    r1=rearth*!pi*(90-abs(lat1[ind]))/180
    r2=rearth*!pi*(90-abs(lat2[ind])/180
    x1=r1*cos(!pi*lon1[ind]/180)
    y1=r1*sin(!pi*lon1[ind]/180)
    x2=r2*cos(!pi*lon2[ind]/180)
    y2=r2*sin(!pi*lon2[ind]/180)
    r[ind]=sqrt((x2-x1)^2+(y2-y1)^2)
  endif

  if cnt2 gt 0 then begin
    dlon=abs(lon2[ind2]-lon1[ind2])
    ind3=where(dlon gt 180, cnt3)
    if cnt3 gt 0 then dlon[ind3]=360-dlon[ind3]
;    print, dlon
    dx=dlon*cos(!pi*(lat1[ind2]+lat2[ind2])/360)
    dy=lat1[ind2]-lat2[ind2]
    r[ind2]=mperdeg*sqrt(dx^2+dy^2)
  endif

  return, r
end


