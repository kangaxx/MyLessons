#include "geoimagebasefunction.h"
#ifndef PRECNUMDPTS
#define PRECNUMDPTS 1e-6
#endif
//将GUI界面上的基本单元：像素与 IO数据中的基本单元综合起来，用以综合平衡数据的实质与展现，画面精确与用户习惯之间的冲突的要求。
//根据已知条件计算当前基本单元情况,最后两个参数是道间距和采样点间距,及刻度线数量（scaleNum）
baseGraphUnit GeoImageBaseFunction::makeBaseUnit(const int &totalLength, const int &dataNum, const eScaleType &type, int &scaleNum, float dtrace, float dns)
{
    return makeBaseUnit(totalLength,dataNum,type,scaleNum,MIN_SCALE_GRID_DISTANCE,dtrace,dns);
}

baseGraphUnit GeoImageBaseFunction::makeBaseUnit(const int &totalLength, const int &dataNum, const eScaleType &type, int &scaleNum, int minDist, float , float )
{
    assert(totalLength > MIN_SCALE_GRID_DISTANCE);
    assert(minDist >= 0);
    baseGraphUnit base;
    int n = 0;
    //算出每个刻度的间距看
    float scaleDist = float(totalLength)/float(dataNum);
    float combDist = scaleDist; //当单个刻度小于最小值时，按5的倍数递增组合刻度的跨度，直到超过最小刻度
    while(int(combDist) < minDist){
        n += INT_SCALE_GRID_NUM_IDENTITY;
        combDist = scaleDist * float(n);
    }

    if (n==0) n = 1;//n == 0说明原始刻度间距ok
    scaleNum = int(dataNum/n);
    base.type = type;
    base.pixCount = combDist;
    base.dataCount = n;
    base.offset = scaleDist / 2.0f > 1.0f ? scaleDist / 2.0f : 0.0f;
    return base;
}

//获取垂直标尺数据刻度
void GeoImageBaseFunction::calculatorVScaleLinePoint(const QPointF &ptOri, const eLabelPosition &lp, int lineSize, float offsetY, int MapWidth,
                                                     QPoint &p1, QPoint &p2)
{
    assert(lineSize > 0);
    int lineType = -1; //1或者-1，左侧的标尺刻度线类型是-1 ，右侧是1，因为左侧的外端点在标准点的左面，需要distance* -1
    switch(lp){
    case Left:{lineType = -1; MapWidth = 0;/*left scale*/ break;}
    case Right:{lineType = 1;break;}
    default:
        throw QString("ERROR: calculator VScale line's point fail by unknow-LabelPosition");
    }

    p1.setX(ptOri.x()+ MapWidth); //左侧刻度尺已经将map宽度置0，以免刻度尺话到数据map图像的右侧去
    p1.setY(ptOri.y() + offsetY); //ori默认是在上方 , 第一个刻度在distance的一半，之后每个刻度与前一个间隔distance

    p2.setX(ptOri.x() + lineType * lineSize + MapWidth);
    p2.setY(ptOri.y() + offsetY);
}

//获取水平刻度尺可读端点坐标。
void GeoImageBaseFunction::calculatorHScaleLinePoint(const QPointF &ptOri, const eLabelPosition &lp, float distance, float offset,
                                                     int disNum, int lineSize,  QPoint &p1, QPoint &p2)
{
    int lineType = -1; //1或者-1，左侧的标尺刻度线类型是-1 ，右侧是1，因为左侧的外端点在标准点的左面，需要distance* -1
    switch(lp){
    case Top:{lineType = -1;break;}
        //    case Bottom:{lineType = 1;break;} // no bottom scale now
    default:
        throw QString("ERROR: calculator VScale line's point fail by unknow-LabelPosition");
    }

    p1.setX(ptOri.x() + distance * float(disNum) + offset); //ori默认是在左侧
    p1.setY(ptOri.y() );

    p2.setX(ptOri.x() + distance * float(disNum) + offset);
    p2.setY(ptOri.y() + lineType * lineSize);
}

void GeoImageBaseFunction::calculatorVScaleTextPoint(const QPoint &p1, const QPoint &p2, const eLabelPosition &lp, QString text, QPoint &pText)
{
    int offsetX = text.size() * 10; //10 pix per Charactar;

    switch(lp){
    case Left:{
        pText.setX((p1.x()+p2.x())/2-offsetX);
        pText.setY(p1.y() - INT_SCALE_TEXT_OVER_LINE);
        break;
    }
    case Right:{
        pText.setX((p1.x()+p2.x())/2);
        pText.setY(p1.y() - INT_SCALE_TEXT_OVER_LINE);
        break;
    }
    default:
        throw QString("ERROR, calculatorVScaleTextPoint get unknow argument[lp]");
    }

}

void GeoImageBaseFunction::calculatorHScaleTextPoint(const QPointF &ptOri, const eLabelPosition &lp, int distance, float offset,
                                                     int disNum, int lineSize, QPoint &p, QString text)
{
    QPoint p1,p2;
    //get line position
    calculatorHScaleLinePoint(ptOri,lp,distance,offset,disNum,lineSize,p1,p2);
    //set text over line end point
    int lineType = -1;
    switch(lp){
    case Top:{lineType = -1;break;}
    default:
        throw QString("ERROR: calculator VScale line's point fail by unknow-LabelPosition");
    }
    int textWidth = text.size() * INT_SCALE_TEXT_CHAR_WIDTH;

    int lineEndY = 0;
    if (lineType < 0)
        lineEndY = p1.y() < p2.y() ? p1.y() : p2.y();
    else
        lineEndY = p1.y() < p2.y() ? p2.y() : p1.y();

    p.setY( lineEndY + lineType * INT_SCALE_TEXT_OVER_LINE);
    p.setX(p1.x()-int(textWidth/2));
}


//固定垂直刻度尺刻度点获取函数，与之前的动态刻度尺的两端需要计算取得不同，固定刻度尺的起始端点是人为设定好的输入参数，本函数只是根据输入的两端坐标及希话绘制成几个刻度，计算出每个刻度点的坐标（包含起始端点）
//scaleBothEnds表示返回刻度数内是否包含了两个端点， 例如，如果scaleNum设置5，包含两端则每个刻度间隔为总高度的1/4，否则间隔位总高度的 1/6
vector<QPointF> GeoImageBaseFunction::calculatorConstVScalePoint(const QPointF &begin, const QPointF &end, float scalePrecent, bool scaleBothEnds)
{
    assert(scalePrecent > 0.0f);
    assert(scalePrecent < 1.0f); //百分比等于1或者大于1理论上也可，但是就变成只有起始端了
    vector<QPointF> result;
    float xDis, yDis; //x，y轴上起始点之间的间隔
    xDis = (end.x() - begin.x());
    yDis = (end.y() - begin.y());
    if (scaleBothEnds){ //如果包含起始端

        result.push_back(begin);
        for (float i = scalePrecent; i < 1.0f; ){
            result.push_back(QPointF(begin.x() + i * xDis, begin.y() + i * yDis));
            i += scalePrecent;
        }
        result.push_back(end);

    }
    else //不包含起始端，返回的单元个数
    {
        for (float i = scalePrecent; i < 1.0f; ){
            result.push_back(QPointF(begin.x() + i * xDis, begin.y() + i * yDis));
            i += scalePrecent;
        }
    }
    return result;
}


//结合刻度坐标使用，这个是算出刻度线旁边的读数来，
//没错，使用的时候外侧包一个函数将两者合并起来会更好哦
vector<float> GeoImageBaseFunction::calculatorConstScaleValue(float min, float max, float scalePrecent, bool scaleBothEnds)
{
    assert(scalePrecent > 0.0f);
    assert(scalePrecent < 1.0f); //百分比等于1或者大于1理论上也可，但是就变成只有起始端了
    vector<float> result;
    float valueDis; //每个刻度的x，y轴读数的差值
    valueDis = (max - min) ;
    if (scaleBothEnds){ //如果包含起始端
        result.push_back(max);
        for (float i = scalePrecent; i < 1.0f; ){
            result.push_back(max - i * valueDis); //绘图时是从大往小绘制的
            i += scalePrecent;
        }
        result.push_back(min);

    }
    else //不包含起始端，返回的单元个数
    {
        for (float i = scalePrecent; i < 1.0f; ){
            result.push_back(max - i * valueDis);
            i += scalePrecent;
        }
    }
    return result;
}

vector<float> GeoImageBaseFunction::getBestScaleNum(float min, float max, int resultNum)
{
    if (max < min) swap(max,min);// max > min !!!
    vector<float> result;
    float disTmp = (max-min)/float(resultNum);

    int size = getHeadNum(disTmp); //获取最高位相对小数点的位置

    int temp = round(disTmp/float(pow(10,size))); //针对最高位做四舍五入 ，注意，round函数在某些操作系统上不是四舍五入而是向下取整。
    float dist = float(temp) * pow(10,size); //除最高位外其他位全部置0
    //最后，判断dist的最高位是否还能再做一次进位，如果进位后新的数据与dist之间的比值小于2，并且 resultNum / 比值 > resultNum - 3 > 2
    //那就再进一位，因为间隔0.1总比0.09好看，间隔100的序列也比80好看（标准是：刻度值内的非0位更少）。
    float BestDist = pow(10,size + 1);
    if (BestDist/dist < 2 && resultNum /int(BestDist/dist) > resultNum - 3 && resultNum /int(BestDist/dist) > 2 )
        dist = BestDist;
    if (dist == 0.0f){
        //特定情况下，max min值实在太小算不出间隔了,可能是max - min == 0
        result.push_back(min);
        if (max > min)
            result.push_back(max);
        return result;
    }

    //dist就是一个最合理的float间隔数， 非0位数只有1个。
    int n = 1;
    while (float(n) * dist <= max){
        if (float(n) * dist > min)
            result.push_back(float(n) * dist);
        n++;
    }
    return result;
}

//根据当前放大倍数，原始取样总数，坐标值（x或y），总长度，算出取样点下标偏移量,注意是偏移量。 f(off) = totalNum * zoom * (X坐标 or Y坐标/rectSize)
//例如，放大倍数为1，总取样点数100个，在长度200的图像轴上的坐标50处取样，取到的数据下标偏移量就是24（从0开始）
int GeoImageBaseFunction::getCurrentIdxOffset(const float &zoom, const int &totalNum, const int &rectSize, const int &XorY)
{
    assert(rectSize > 0);
    float tmp = zoom * float(XorY) / float(rectSize);
    return int(float(totalNum) * tmp);
}

void GeoImageBaseFunction::calculatorVGridLinePoint(const QPointF &ptOri, const float &distance, const float &offset, const int &height, int disNum, QPointF &p1, QPointF &p2)
{
    p1.setX(ptOri.x() + distance * float(disNum) + offset); //ori默认是在左侧
    p1.setY(ptOri.y() );

    p2.setX(ptOri.x() + distance * float(disNum) + offset);
    p2.setY(ptOri.y() + height);
}

void GeoImageBaseFunction::calculatorHGridLinePoint(const QPointF &ptOri, const int &offsetY, const int &width, QPointF &p1, QPointF &p2)
{
    p1.setX(ptOri.x() ); //ori默认是在左侧
    p1.setY(ptOri.y() + offsetY);

    p2.setX(ptOri.x() + width);
    p2.setY(ptOri.y() + offsetY);
}

float GeoImageBaseFunction::getPointByValue(const float &data, const float &dataLimit, const int &base, const float &offset, const int &phase)
{
    return float(base) + data * phase * offset / dataLimit;
}

//返回一个合理的波形图step，确保每道数据宽度至少一个像素
int GeoImageBaseFunction::getGoodStep(int width, int step, int horizNum)
{
    assert(step > 0);
    assert(width > 0);
    assert(horizNum > 0);
    int result,hNum;
    int time = 1;

    do {
        result = step * time++;
        hNum = horizNum/result + (horizNum % result == 0 ? 0 : 1);
    }
    while (hNum > width);
    return result;
}



//将缩放后的坐标还原位原始坐标
int GeoImageBaseFunction::zoomd2org(int in, float zoom, int dataIdx, int dataNum, int screen_len)
{
    int rst = zoomd2orgF(in, zoom, dataIdx, dataNum, screen_len);
    return rst;
}

float GeoImageBaseFunction::zoomd2orgF(int in, float zoom, int dataIdx, int dataNum, int screen_len)
{
    assert(dataNum > 0);
    float rst =  float (in) * float(zoom)  +  float(dataIdx) * float(screen_len) / float(dataNum);
    return rst;
}

//将原始坐标转换成缩放后的坐标 ，与上面的公式可以互推才对
int GeoImageBaseFunction::org2zoomd(int in, float zoom, int dataIdx, int dataNum, int screen_len)
{
    int rst = org2zoomdF(in, zoom, dataIdx, dataNum, screen_len);
    return rst;
}

float GeoImageBaseFunction::org2zoomdF(int in, float zoom, int dataIdx, int dataNum, int screen_len)
{
    assert(zoom > 0.0f);
    assert(dataNum > 0);
    float rst = float (in)  - float(dataIdx) * float(screen_len) / float (dataNum);
    rst = float(rst) / zoom;
    return rst;
}

QPointF GeoImageBaseFunction::org2zoomd(QPointF in, float zoom_x, float zoom_y, int horizIdx, int vertIdx, int horizNum, int vertNum, int width, int height)
{
    float x = org2zoomdF(in.x(), zoom_x, horizIdx, horizNum, width);
    float y = org2zoomdF(in.y(), zoom_y, vertIdx, vertNum, height);
    return QPointF(x, y);
}

QPointF GeoImageBaseFunction::zoomd2org(QPointF in, float zoom_x, float zoom_y, int horizIdx, int vertIdx, int horizNum, int vertNum, int width, int height)
{
    float x = zoomd2org(in.x(), zoom_x, horizIdx, horizNum, width);
    float y = zoomd2org(in.y(), zoom_y, vertIdx, vertNum, height);
    return QPointF(x, y);
}

int GeoImageBaseFunction::getRandomFloat(float *out, int num)
{
    srand((unsigned )time(0));
    int result = 0;
    for (;result <= num; result++)
        out[result] = 200.0f * rand() / RAND_MAX;
    return result;
}

float GeoImageBaseFunction::getLoggingValue(float in, int zoomedDataNum, int beginIdx, int length)
{
    assert(in > 0.0f);
    float distance = float(length) / float (zoomedDataNum); //每道宽度
    return float(in - beginIdx) * distance + distance / 2.0f;
}

QPointF GeoImageBaseFunction::getLoggingPoint(float logX, float logY,
                                              int zoomedHorizNum, int zoomedVertNum,
                                              int horizBeginIdx, int vertBeginIdx,
                                              int width, int height)
{
    return QPointF(getLoggingValue(logX, zoomedHorizNum, horizBeginIdx, width),
                   getLoggingValue(logY, zoomedVertNum, vertBeginIdx, height));
}

QPointF GeoImageBaseFunction::getLoggingWavePoint(QPointF p1, QPointF p2, float len)
{
    double adjAngle = M_PI_2;

    double dx = p2.x() - p1.x();
    double dy = p2.y() - p1.y();
    double ang;
    if (dx == 0) ang = M_PI_2;
    else
        ang = atan(dy / dx);  //负数角的inc会在右侧，正数角的dec会在右侧(第一向限,实际显示时会受设备影响)
    if (ang > 0)
        adjAngle *= -1;
    double waveAng = adjAngle + ang;
    double directAdj = 1.0;  //此参数专为解决180度叫cos sin函数错误而设 ， 勿做他用
    if (waveAng == M_PI){
        waveAng = 0.0; //math.h在180度上的sin cos不正确，很容易验证的
        directAdj = -1.0;
    }

    double dyInc = sin(waveAng) * len * directAdj;
    double dxInc = cos(waveAng) * len * directAdj;
    //    qDebug() << QString("p1.x : %1, p1.y : %2, p2.x : %3, p2.y : %4").arg(p1.x()).arg(p1.y())
    //                .arg(p2.x()).arg(p2.y());
    //    qDebug() << QString("dx : %1, dy : %2, angle : %3, len : %4").arg(dxInc).arg(dyInc).arg((adjAngle + ang) * 90.0f/ M_PI_2)
    //                .arg(len);
    return QPointF(p2.x() + dxInc, p2.y() + dyInc);
}

float GeoImageBaseFunction::getWaveLen(float max, float min, float value, float dist)
{
    // DIST/2  :  result = (max-min)/2  : (value - (max/2 - min/2))
    if (max == min) return 0;
    return dist * (value - (max - min) / 2.0f) / (max - min);
}

float GeoImageBaseFunction::getDistanceToLevel(QPointF p, vector<QPointF> level)
{
    int size = level.size();
    assert(size >= 0);
    float *x = new float[size];
    float *y = new float[size];
    for (int i = 0; i < size; ++i){
        x[i] = level.at(i).x();
        y[i] = level.at(i).y();
    }
    float result = distance_point_to_surface_2D(level.size(), p.x(), p.y(), x, y);
    delete [] x;
    delete [] y;
    return result;

}

bool GeoImageBaseFunction::isPointInRect(QPoint pt, QRect rect)
{
    return rect.contains(pt, false);
}

bool GeoImageBaseFunction::isLineInRect(QLine line, QRect rect)
{
    //先判断一下，线段端点是否在rect内部，如果是这样的话直接返回true
    if (rect.contains(line.x1(), line.y1()) ||
            rect.contains(line.x2(), line.y2())    )
        return true;

    int xMin, xMax, yMin, yMax;

    xMin = min(line.p1().x(), line.p2().x());
    xMax = max(line.p1().x(), line.p2().x());
    yMin = min(line.p1().y(), line.p2().y());
    yMax = max(line.p1().y(), line.p2().y());
    //算出 y = ax + b
    // ax1 + b = y1
    // ax2 + b = y2

    // a (x1 - x2 ) =  y1 - y2;
    // a = (y1 - y2) / (x1 - x2)
    // b = y1 - ax1

    // x = (y - b) / a
    float a, b;
    if (line.x1() != line.x2() && line.y1() != line.y2())
    {
        //斜线
        a = float(line.y1() - line.y2()) / float(line.x1() - line.x2());
        b = float(line.y1()) - a * float(line.x1());
        //判断是否和区域上端相交
        float top_intersect =  (float(rect.top()) - b) / a;
        if (top_intersect >= float(rect.left()) && top_intersect <= float(rect.right())
                && top_intersect >= float(xMin) && top_intersect <= float(xMax))
            return true;

        //判断是否和区域下端相交
        float bottom_intersect = (float(rect.bottom()) - b) / a;
        if (bottom_intersect >= float(rect.left()) && bottom_intersect <= (rect.right())
            && bottom_intersect >= float(xMin) && bottom_intersect <= float(xMax))
            return true;

        //判断是否和区域左侧相交
        float left_intersect = a * (rect.left()) + b;
        if (left_intersect >= float(rect.top()) && left_intersect <= float(rect.bottom())
                && left_intersect >= float(yMin) && left_intersect <= float(yMax))
            return true;

        //判断是否和区域右侧相交
        float right_intersect = a * (rect.right()) + b;
        if (right_intersect >= float(rect.top()) && right_intersect <= float(rect.bottom())
                && right_intersect >= float(yMin) && right_intersect <= float(yMax))
            return true;
    }

    else if (line.x1() != line.x2())
    {
        //横线

        //要么至少有一端在区域内,但实际上一开始就判断过了
        //所以只要判断是否有另一种可能
        //就是横切区域
        if (line.x1() < rect.left() && line.x2() > rect.right()
                && line.y1() >= rect.bottom() && line.y1() <= rect.top())
            return true;
    }

    else if (line.y1() != line.y2())
    {
        //竖线
        //要么至少有一端在区域内,和横线一样，一开始就判断过了
        //所以只要判断是否纵切区域
        if (line.y1() < rect.top() && line.y2() > rect.bottom()
                && line.x1() >= rect.left() && line.x1() <= rect.right())
            return true;
    }
    return false;

}

float GeoImageBaseFunction::getPointInNewMap(int oriMax, int oriMin, int newMax, int newMin, float oriValue)
{
    if (oriMax == newMax && oriMin == newMin)
        return oriValue;
    //newValue / (newMax - newMin) - newMin = oriValue / (oriMax - oriMin) - oriMin
    // newValue = (oriValue / (oriMax - oriMin) - oriMin) * (newMax - newMin) + newMin
    return  (oriValue / float(oriMax - oriMin) - float(oriMin)) * float(newMax - newMin) + float(newMin);
}


int GeoImageBaseFunction::getHeadNum(float t)
{
    if (t == 0.0f)
        return 0;
    int result = 0;
    if (fabs(t) > 1.0f){
        result = -1;
        while (t > 1.0f ){
            result++;
            t /= 10.0f;
        }
    }
    else{
        while (t < 1.0f ){
            result--;
            t *= 10.0f;
        }
    }
    return result;
}

float GeoImageBaseFunction::distance_point_to_surface_2D(int nps, float xp, float zp, float *xs, float *zs)
{
    int		ipst, ips_adj;
    float	dis_order, xa, za, xb, zb, xn, zn, dx_pts, dz_pts, ftmp1, ftmp2;

    //----------------------------------------------------------------------------------------------
    //首先找到面上最近的点
    ips_adj = 0;
    ftmp1 = pow (xp-xs[0], 2.) + pow (zp-zs[0], 2.);
    for (ipst=1; ipst<nps; ipst++)
    {
        ftmp2 = pow (xp-xs[ipst], 2.) + pow (zp-zs[ipst], 2.);
        if (ftmp2 < ftmp1)
        {
            ips_adj = ipst;
            ftmp1 = ftmp2;
        }
    }

    // 估计点之间的一般距离
    dis_order = sqrt (pow (xs[1]-xs[0], 2.) + pow (zs[1]-zs[0], 2.));
    dis_order += sqrt (pow (xs[nps-1]-xs[nps-2], 2.) + pow (zs[nps-1]-zs[nps-2], 2.));
    dis_order *= 0.5;

    //----------------------------------------------------------------------------------------------
    //如果第0个点或最后的点最近
    if (0 == ips_adj || nps-1 == ips_adj)
    {
        return sqrt (pow (xp-xs[ips_adj], 2.) + pow (zp-zs[ips_adj], 2.));
    }
    //其它的点最近
    else
    {
        for (ipst=ips_adj-1; ipst<ips_adj+1; ipst++)
        {
            xa = xs[ipst];
            za = zs[ipst];
            xb = xs[ipst+1];
            zb = zs[ipst+1];
            dx_pts = xb - xa;
            dz_pts = zb - za;

            //如果局部的线与z轴平行
            if (fabs(dx_pts) < dis_order*PRECNUMDPTS)
            {
                zn = zp;
                if ((zn >= za && zn <= zb) || (zn <= za && zn >= zb))
                {
                    xn = xa;
                    return sqrt (pow (xp-xn, 2.) + pow (zp-zn, 2.));
                }
            }
            else
            {
                xn = (dx_pts * dx_pts * xp + dz_pts * dz_pts * xa
                      + dx_pts * dz_pts * (zp - za))
                        / (dx_pts * dx_pts + dz_pts * dz_pts);
                if ((xn >= xa && xn <= xb) || (xn <= xa && xn >= xb))
                {
                    zn = dz_pts * (xn - xa) / dx_pts + za;
                    return sqrt (pow (xp-xn, 2.) + pow (zp-zn, 2.));
                }
            }
        }

        //如果通过上述过程找不到垂足，则把最近的点当作垂足。
        xn = xs[ips_adj];
        zn = zs[ips_adj];
        return sqrt (pow (xp-xn, 2.) + pow (zp-zn, 2.));
    }
}




