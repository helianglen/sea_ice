C **********
C **********
      SUBROUTINE CKW(FNU,T,S,epsp,epspp)
C CKW=COMPLEX DIELECTRIC CONSTANT OF SEA WATER WHOSE TEMPERATURE IS
C T DEGREES KELVIN AND WHOSE SALINITY IS S PARTS PER THOUSAND AT THE
C FREQUENCY FNU GHZ
      IMPLICIT REAL*8(A,B,D-H,O-Z),COMPLEX*16(C)
      TC=T-.273D3
      EP0=.8774D2-TC*(.40008-TC*(.9398D-3-.141D-5*TC))
      DELAM=FNU*(.111093-TC*(.38236D-2-TC*(.69375D-4-.50963D-6*TC)))
      IF(S.EQ.0.D0)GO TO 1
      XN=S*(.1707D-1+S*(.12053D-4+.40575D-8*S))
      F=1.D0-XN*(.255059-XN*(.51514D-1-.68889D-2*XN))
      EP0=EP0*F
      F=1.D0-XN*(.48963D-1+XN*(.29667D-1-.56444D-2*XN))
      DELAM=DELAM*(F+.1463D-2*XN*TC)
1     EP1=(EP0-.49D1)/(1.D0+DELAM*DELAM)
      B=DELAM*EP1
      IF(S.EQ.0.D0)GO TO 2
      SIG=S*(.1825208-S*(.146192D-2-S*(.209324D-4-.128205D-6*S)))
      TAU=.25D2-TC
      A=.203318D-1+TAU*(.12664D-3+.24637D-5*TAU)-S*(.184911D-4-TAU*(.255
     .06D-6-.25506D-7*TAU))
      SIGMA=SIG*DEXP(-TAU*A)
      B=B+SIGMA/(.55632485D-1*FNU)
2     cum=DCMPLX(.49D1+EP1,B)
      epsp=.49D1+ep1
      epspp=b
c      write(*,*) fnu, t, s
c      write(*,*) epsp, epspp
      RETURN
      END
C **********
