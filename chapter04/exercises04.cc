#include <algorithm>
#include <iterator>
#include <type_traits>
#include <opencv2/opencv.hpp>
using namespace std;

static const int numW = 10;
static const int numH = 20;

template <typename T = uchar>
class ASCIINumber
{
private:
    static const int row = numH;
    static const int col = numW;
    int num;
    T foreground;
    T background;
    cv::Mat_<T> m;

    void fillMatZero()
    {
        for (int i = 2; i < 8; i++)
        {
            m(2, i) = foreground;
            m(17, i) = foreground;
        }
        for (int i = 3; i < 17; i++)
        {
            m(i, 2) = foreground;
            m(i, 7) = foreground;
        }
    }

    void fillMatOne()
    {
        for (int i = 2; i < 8; i++)
        {
            m(17, i) = foreground;
        }
        for (int i = 3; i < 17; i++)
        {
            m(i, 5) = foreground;
        }
        m(5, 2) = foreground;
        m(4, 3) = foreground;
        m(3, 4) = foreground;
        m(2, 5) = foreground;
    }

    void fillMatTwo()
    {
        for (int i = 2; i < 8; i++)
        {
            m(2, i) = foreground;
            m(9, i) = foreground;
            m(17, i) = foreground;
        }
        for (int i = 3; i < 9; i++)
        {
            m(i, 7) = foreground;
        }
        for (int i = 10; i < 17; i++)
        {
            m(i, 2) = foreground;
        }
    }

    void fillMatThree()
    {
        for (int i = 2; i < 8; i++)
        {
            m(2, i) = foreground;
            m(9, i) = foreground;
            m(17, i) = foreground;
        }
        for (int i = 3; i < 9; i++)
        {
            m(i, 7) = foreground;
        }
        for (int i = 10; i < 17; i++)
        {
            m(i, 7) = foreground;
        }
    }

    void fillMatFour()
    {
        for (int i = 2; i < 8; i++)
        {
            m(10, i) = foreground;
        }
        for (int i = 2; i < 18; i++)
        {
            m(i, 5) = foreground;
        }
        m(4, 4) = foreground;
        m(5, 4) = foreground;
        m(6, 3) = foreground;
        m(7, 3) = foreground;
        m(8, 3) = foreground;
        m(9, 2) = foreground;
        m(10, 2) = foreground;
    }

    void fillMatFive()
    {
        for (int i = 2; i < 8; i++)
        {
            m(2, i) = foreground;
            m(9, i) = foreground;
            m(17, i) = foreground;
        }
        for (int i = 3; i < 9; i++)
        {
            m(i, 2) = foreground;
        }
        for (int i = 10; i < 17; i++)
        {
            m(i, 7) = foreground;
        }
    }

    void fillMatSix()
    {
        for (int i = 2; i < 8; i++)
        {
            m(2, i) = foreground;
            m(9, i) = foreground;
            m(17, i) = foreground;
        }
        for (int i = 3; i < 17; i++)
        {
            m(i, 2) = foreground;
        }
        for (int i = 10; i < 17; i++)
        {
            m(i, 7) = foreground;
        }
    }

    void fillMatSeven()
    {

        for (int i = 2; i < 8; i++)
        {
            m(2, i) = foreground;
        }
        for (int i = 3; i < 6; i++)
        {
            m(i, 7) = foreground;
        }
        for (int i = 6; i < 10; i++)
        {
            m(i, 6) = foreground;
        }
        for (int i = 10; i < 14; i++)
        {
            m(i, 5) = foreground;
        }
        for (int i = 14; i < 18; i++)
        {
            m(i, 4) = foreground;
        }
    }

    void fillMatEight()
    {
        for (int i = 2; i < 8; i++)
        {
            m(2, i) = foreground;
            m(9, i) = foreground;
            m(17, i) = foreground;
        }
        for (int i = 3; i < 17; i++)
        {
            m(i, 2) = foreground;
        }
        for (int i = 3; i < 17; i++)
        {
            m(i, 7) = foreground;
        }
    }
    void fillMatNine()
    {
        for (int i = 2; i < 8; i++)
        {
            m(2, i) = foreground;
            m(9, i) = foreground;
            m(17, i) = foreground;
        }
        for (int i = 3; i < 17; i++)
        {
            m(i, 7) = foreground;
        }
        for (int i = 3; i < 10; i++)
        {
            m(i, 2) = foreground;
        }
    }

    void fillMatNone()
    {
        for(typename cv::Mat_<T>::iterator it = m.begin(); it != m.end(); ++it)
        {
            *it = background;
        }
    }
public :

    ASCIINumber(int n, const T& fg =T(255,255,255), const T& bg =T(0,0,0)): num(n), foreground(fg), background(bg)
    {
        m = cv::Mat_<T>(row, col, background);
        switch (n)
        {
        case 48: // '0'
            fillMatZero();
            break;
        case 49: // '1'
            fillMatOne();
            break;
        case 50: // '2'
            fillMatTwo();
            break;
        case 51: // '3'
            fillMatThree();
            break;
        case 52: // '4'
            fillMatFour();
            break;
        case 53: // '5'
            fillMatFive();
            break;
        case 54: // '6'
            fillMatSix();
            break;
        case 55: // '7'
            fillMatSeven();
            break;
        case 56: // '8'
            fillMatEight();
            break;
        case 57: // '9'
            fillMatNine();
            break;
        case 32: // space
            fillMatNone();
            break;
        default:
            fillMatNone();
            break;
        }

    }

    cv::Mat_<T> getAsciiMatNumber() const
    {
        return m;
    }

    int getNumber()
    {
        return num;
    }

    T getForeground()
    {
        return foreground;
    }
};


template <typename T = uchar>
class Display
{
private:
    static const int row = numH*25;
    static const int col = numW*50;
    cv::Mat_<T> screen;
    cv::Point2i currentPos;
    T bgColor;
    T fgColor;
    bool flash;

    bool compare(const cv::Mat_<T>& s1, const cv::Mat_<T>& s2)
    {
        typename cv::Mat_<T>::const_iterator it1 = s1.begin();
        typename cv::Mat_<T>::const_iterator it2 = s2.begin();
        for(;it1 != s1.end(); ++it1, ++it2)
        {
            if(*it1 != *it2)
            {
                return false;
            }
        }
        return true;
    }

    void mouseBlinks(bool on)
    {
        T corlor;
        if(currentPos.y >= row)
        {
            return;
        };

        if(on)
        {
            corlor = fgColor;
        }
        else
        {
            corlor = bgColor;
        }
        cv::Mat_<T> mm = screen(cv::Rect(currentPos.x, currentPos.y, 1, numH));
        typename cv::Mat_<T>::iterator itD = mm.begin();
        for(;itD != mm.end(); ++itD)
        {
            *itD = corlor;
        }
    }

    void fillChar( ASCIINumber<T>& c)
    {
        cv::Mat_<T> mm = screen(cv::Rect(currentPos.x, currentPos.y, numW, numH));

        typename cv::Mat_<T>::iterator itD = mm.begin();
        typename cv::Mat_<T>::const_iterator itn = c.getAsciiMatNumber().begin();

        for(;itD != mm.end(); ++itD, ++itn)
        {
            *itD = *itn;
        }
    }

    void fillChar(const ASCIINumber<T>& c, int x, int y) const
    {
        cv::Mat_<T> mm = screen(cv::Rect(x, y, numW, numH));

        typename cv::Mat_<T>::iterator itD = mm.begin();
        typename cv::Mat_<T>::iterator itn = c.getAsciiMatNumber().begin();

        for(;itD != mm.end(); ++itD, ++itn)
        {
            *itD = *itn;
        }
    }

    void inputChar(int c)
    {
        ASCIINumber<T> ch(c, fgColor, bgColor);
        if(currentPos.y >= row)
        {
            cout << "full" << endl;
            return;
        }
        mouseBlinks(false);   // clear mouse blinks
        fillChar(ch);
        currentPos.x += numW;
        if(currentPos.x >= col)
        {
            currentPos.x = 0;
            currentPos.y += numH;
        };
    }

    void inputBackspace()
    {
        if(currentPos.x == 0 && currentPos.y== 0)
        {
            cout << "begin" << endl;
            return;
        }
        mouseBlinks(false);   // clear mouse blinks
        if(currentPos.x == 0)
        {
            currentPos.y -= numH;
            currentPos.x =col - numW;
        }
        else
        {
            currentPos.x -= numW;
        }
        ASCIINumber<T> space(32, bgColor, bgColor);
        fillChar(space);
        return;

    }

    void inputEnterKey()
    {
        mouseBlinks(false);   // clear mouse blinks
        if(currentPos.y >= row - numH)
        {
            cout << "end" << endl;
            currentPos.y = row - numH;
            return;
        }
        currentPos.y += numH;
        currentPos.x = 0;
    }

    void inputArrowKey(int c)
    {
        mouseBlinks(false);   // clear mouse blinks
        switch (c)
        {
        case 81: // left arrow
            if(currentPos.x >= numW)
            {
                currentPos.x -= numW;
            }
            break;

        case 82:  // up arrow
            if(currentPos.y >= numH)
            {
                currentPos.y -= numH;
            }
            break;

        case 83: // right arrow
            if(currentPos.x <= (col - numW))
            {
                currentPos.x += numW;
            }
            break;

        case 84: // down arrow
            if(currentPos.y >= (row - numH))
            {
                currentPos.y += numH;
            }
            break;

        default:
            break;
        }
    }
public:
    Display(const T& fg = T(255,255,255), const T& bg = T(0, 0 ,0)):fgColor(fg), bgColor(bg), currentPos(cv::Point2i(0,0))
    {
        screen = cv::Mat_<T>(row, col, bgColor);
        cv::namedWindow("Typewriter", cv::WINDOW_AUTOSIZE);
        cv::imshow("Typewriter", screen);
    }

    ~Display()
    {
        cv::waitKey(0);
        cv::destroyWindow("Typewriter");
    }



    int waitKey(int t = 0)
    {
        return  cv::waitKey(t);
    }

    void input(int c)
    {
        cout << "input :"<< c << endl;
        mouseBlinks(flash=(!flash));
        if(c == 10) // enter key
        {
            inputEnterKey();
        }
        else if(c == 8)  // backspace
        {
            inputBackspace();
        }
        else if (c == 32) // space
        {
            inputChar(c);
        }
        else if (c >= '0' &&  c <= '9')
        {
            inputChar(c);
        }
        else if(c >= 81 && c <= 84)
        {
            inputArrowKey(c);
        }
        else if(c == 'c')  // covert
        {
            converNumColor();
        }
        cv::imshow("Typewriter", screen);
    }

    cv::Point2i getCurrentPos()
    {
        return currentPos;
    }

    void converNumColor()
    {
        ASCIINumber<T> zero(0+'0', fgColor, bgColor);
        ASCIINumber<T> one(1+'0', fgColor, bgColor);
        ASCIINumber<T> two(2+'0', fgColor, bgColor);
        ASCIINumber<T> three(3+'0', fgColor, bgColor);
        ASCIINumber<T> four(4+'0', fgColor, bgColor);
        ASCIINumber<T> five(5+'0', fgColor, bgColor);
        ASCIINumber<T> six(6+'0', fgColor, bgColor);
        ASCIINumber<T> seven(7+'0', fgColor, bgColor);
        ASCIINumber<T> eight(8+'0', fgColor, bgColor);
        ASCIINumber<T> nine(9+'0', fgColor, bgColor);

        for(int x = 0; x < col; x += numW)
        {
            for(int y = 0; y < row; y += numH)
            {
                cv::Mat_<T> mm = screen(cv::Rect(x, y, numW, numH));
                if(compare(mm , zero.getAsciiMatNumber()))
                {
                    fillChar(ASCIINumber<T> (0+'0', T(255-10, 255-100, 255-10), bgColor), x, y);
                    cout << "conver 0" << endl;
                }
                else if(compare(mm , one.getAsciiMatNumber()))
                {
                    fillChar(ASCIINumber<T> (1+'0', T(255-20, 255-90, 255-20), bgColor), x, y);
                    cout << "conver 1" << endl;
                }
                else if(compare(mm , two.getAsciiMatNumber()))
                {
                    fillChar(ASCIINumber<T> (2+'0', T(255-30, 255-80, 255-30), bgColor), x, y);
                    cout << "conver 2" << endl;
                }
                else if(compare(mm , three.getAsciiMatNumber()))
                {
                    fillChar(ASCIINumber<T> (3+'0', T(255-40, 255-70, 255-40), bgColor), x, y);
                    cout << "conver 3" << endl;
                }
                else if(compare(mm , four.getAsciiMatNumber()))
                {
                    fillChar(ASCIINumber<T> (4+'0', T(255-50, 255-60, 255-50), bgColor), x, y);
                    cout << "conver 4" << endl;
                }
                else if(compare(mm , five.getAsciiMatNumber()))
                {
                    fillChar(ASCIINumber<T> (5+'0', T(255-60, 255-50, 255-60), bgColor), x, y);
                    cout << "conver 5" << endl;
                }
                else if(compare(mm , six.getAsciiMatNumber()))
                {
                    fillChar(ASCIINumber<T> (6+'0', T(255-70, 255-40, 255-70), bgColor), x, y);
                    cout << "conver 6" << endl;
                }
                else if(compare(mm , seven.getAsciiMatNumber()))
                {
                    fillChar(ASCIINumber<T> (7+'0', T(255-80, 255-30, 255-80), bgColor), x, y);
                    cout << "conver 7" << endl;
                }
                else if(compare(mm , eight.getAsciiMatNumber()))
                {
                    fillChar(ASCIINumber<T> (8+'0', T(255-90, 255-20, 255-90), bgColor), x, y);
                    cout << "conver 8" << endl;
                }
                else if(compare(mm , nine.getAsciiMatNumber()))
                {
                    fillChar(ASCIINumber<T> (9+'0', T(255-100, 255-10, 255-100), bgColor), x, y);
                    cout << "conver 9" << endl;
                }
            }
        }
    }
};


int main()
{
#if 1
    Display<cv::Vec3b> d;
#else
    Display<uchar> d;
#endif
    int c = 0;

    while((c = d.waitKey(500)) != 27) // esc
    {
        d.input(c);
    }

}
