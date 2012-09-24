# bash roc.sh labels predictions

DISPLAY=:1
echo "
library(verification)
y=read.table('$1')[[1]]
d=read.table('$2')[[1]]
d=d-min(d)
d=d/max(d)
y=y/2+0.5
area=roc.area(y,d)
print(area)
#postscript('ROC.eps',horizontal=FALSE,width=4,height=4)
#roc.plot(y,d)
#dev.off()
"|R --vanilla
