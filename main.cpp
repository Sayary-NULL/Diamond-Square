#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <unistd.h>
#include <SFML/Graphics.hpp>

const unsigned int SET_WIDTH = 1025;
const unsigned int SET_HEIGHT = 1025;
const double DSET_WIDTH = 1025.0;
const double DSET_HEIGHT = 1025.0;
const double RMAX = 150.0;
const double RMIN = 0.0;

class RandomM
{
    std::default_random_engine rand_gen;

public:
    RandomM()
    {
        rand_gen = std::default_random_engine (static_cast<double>(std::chrono::system_clock::now().time_since_epoch().count()));
    }

    RandomM(int number)
    {
        rand_gen = std::default_random_engine (static_cast<double>(number));
    }

    double Random(double min, double max)
    {
        std::uniform_real_distribution<double> rand_distr = std::uniform_real_distribution<double>(min, static_cast<double>(max));
        return rand_distr(rand_gen);
    }
};

RandomM RandM(124);

double sumSr(std::vector<std::vector<double>> &_array, int x, int y, int len)
{
    double s1, s2, s3, s4;
    s1 = _array[x][y + len];
    s2 = _array[x][y - len];
    s3 = _array[x + len][y];
    s4 = _array[x - len][y];

    return (s1 + s2 + s3 + s4) / 4.0;
}

void proxod(std::vector<std::vector<double>> &_array, int len, double R, int X, int Y)
{
    for(int slen = len -1; slen >= 2; slen /=2)
    {
        for(int x = X; x < len - 1 + X; x += slen)
            for(int y = Y; y < len - 1 + Y; y += slen)
            {
                if (_array[x + slen / 2][y + slen / 2] == 0.0)
                {
                    double sr = (_array[x][y] + _array[x + slen][y] + _array[x][y + slen] +
                                 _array[x + slen][y + slen]) / 4 + RandM.Random(-R * slen, R * slen);
                    _array[x + slen / 2][y + slen / 2] = sr;
                }
            }

        for(int x = X; x < len - 1 + X; x += slen)
            for(int y = Y; y < len - 1 + Y; y += slen)
            {
                if(_array[x][y + slen / 2] == 0)
                _array[x][y + slen / 2] = sumSr(_array, x, y + slen / 2, slen / 2) + RandM.Random(-R * slen, R * slen);
                if(_array[x + slen / 2][y] == 0)
                _array[x + slen / 2][y] = sumSr(_array, x + slen / 2, y, slen / 2) + RandM.Random(-R * slen, R * slen);
                if(_array[x + slen / 2][y + slen] == 0)
                _array[x + slen / 2][y + slen] = sumSr(_array, x + slen / 2, y + slen, slen / 2) + RandM.Random(-R * slen, R * slen);
                if(_array[x + slen][y + slen / 2] == 0)
                _array[x + slen][y + slen / 2] = sumSr(_array, x + slen, y + slen / 2, slen / 2) + RandM.Random(-R * slen, R * slen);
            }

        //break;
    }
}
std::vector<std::pair<int, int>> sh2;
void proxod2(std::vector<std::vector<double>> &_array, int len, double R, int X, int Y)
{
    //for(int slen = len -1; slen >= 2; slen /=2)
    for(int slen = len -1; slen >= 2; slen /=2)
    {
        for(int x = X; x < len - 1 + X; x += slen)
            for(int y = Y; y < len - 1 + Y; y += slen)
            {
                if (_array[x + slen / 2][y + slen / 2] == 0.0)
                {
                    double sr = (_array[x][y] + _array[x + slen][y] + _array[x][y + slen] +
                                 _array[x + slen][y + slen]) / 4 + RandM.Random(-R * slen, R * slen);
                    _array[x + slen / 2][y + slen / 2] = sr;
                }
            }

        for(int x = X; x < len - 1 + X; x += slen)
            for(int y = Y; y < len - 1 + Y; y += slen)
            {
                //if(_array[x][y + slen / 2] == 0)
                    _array[x][y + slen / 2] = sumSr(_array, x, y + slen / 2, slen / 2) + RandM.Random(-R * slen, R * slen);
                //if(_array[x + slen / 2][y] == 0)
                    _array[x + slen / 2][y] = sumSr(_array, x + slen / 2, y, slen / 2) + RandM.Random(-R * slen, R * slen);
                //if(_array[x + slen / 2][y + slen] == 0)
                    _array[x + slen / 2][y + slen] = sumSr(_array, x + slen / 2, y + slen, slen / 2) + RandM.Random(-R * slen, R * slen);
               // if(_array[x + slen][y + slen / 2] == 0)
                    _array[x + slen][y + slen / 2] = sumSr(_array, x + slen, y + slen / 2, slen / 2) + RandM.Random(-R * slen, R * slen);
            }

        //break;
    }
}

void Diad(std::vector<std::vector<double>> &_array, int X1, int Y1, int X2, int Y2, int R)
{
    if(abs(X1 - X2) <= 1)
        return;

    int midpX = abs(X1 + X2)/2,
            midpY = abs(Y1 + Y2)/2;
    double a = sqrt(pow(X1 - X2, 2)*pow(Y1 - Y2, 2));
    double srzn = (_array[X1][Y1] + _array[X2][Y2])/2 + RandM.Random(-R*a, R*a);
    _array[midpX][midpY] = srzn;
    Diad(_array, X1, Y1, midpX, midpY, R);
    Diad(_array, midpX, midpY, X2, Y2, R);
}

void FullingMap(std::vector<std::vector<double>> &_array, int len, int R)
{
    int lenArray = _array.size();
    int xy = lenArray / 4;
    int max = 150;
    _array[xy][xy] = RandM.Random(0, max);
    _array[xy][xy + len - 1] = RandM.Random(0, max);
    _array[xy + len - 1][xy] = RandM.Random(0, max);
    _array[xy + len - 1][xy + len - 1] = RandM.Random(0, max);

    _array[0][lenArray/2] = RandM.Random(0, max);
    _array[lenArray/2][0] = RandM.Random(0, max);
    _array[lenArray/2][lenArray - 1] = RandM.Random(0, max);
    _array[lenArray - 1][lenArray/2] = RandM.Random(0, max);

    /*Diad(_array, 0, lenArray/2, lenArray/2, 0, R);
    Diad(_array, lenArray/2, 0, lenArray-1, lenArray/2, R);
    Diad(_array, lenArray-1, lenArray/2, lenArray/2, lenArray - 1, R);
    Diad(_array, 0, lenArray/2, lenArray/2, lenArray - 1, R);*/
}

void Scale(std::vector<std::vector<double>> &_array, int len, int X, int Y, double R = 0.6)
{
    //работает но оттенки не идут
    for(int i = Y; i < Y + len; i++)
        _array[X][i] = 0;
    for(int slen = len/2; slen >= 1; slen /= 2)
    {
        for(int y = Y; y <= Y + len; y += slen)
        {
            /*if(_array[X][y] != 0)
                continue;*/
            double s1, s2, s3, s4;
            //sh2.push_back(std::pair<int, int>(X + slen,y));
            s1 = _array[X + 1][y];
            //sh2.push_back(std::pair<int, int>(X - slen,y));
            s2 = _array[X - 1][y];
            //sh2.push_back(std::pair<int, int>(X,y - slen));
            s3 = _array[X][y - 1];
            //sh2.push_back(std::pair<int, int>(X,y + slen));
            //s4 = _array[X][y + 1];
            _array[X][y] = (s1+s2+s3)/3.0 ;//+ RandM.Random(-R*slen, R*slen);
            //break;
        }
    }
}

sf::Color SelectColor(double X)
{
    int ret = X / 30;
    ret *= 30;
    return sf::Color(ret, ret, ret);
    //return sf::Color(X, X, X);
    if(X < 64)
        return sf::Color::Blue;
    else if(X < 128)
        return sf::Color(150, 75, 0);
    else if(X < 256)
        return sf::Color(123, 63, 0);
    else return sf::Color::Yellow;
}

int main()
{
    int n = 8;
    int len = pow(2, n) + 1;
    int lenVect = pow(2, n + 1) + 1;
    double block_size = DSET_WIDTH / len;
    double R = 0.6;
    std::vector<std::vector<double>> _array(lenVect, std::vector<double>(lenVect, 0.0));
    std::cout << "установлена размерность: " << len << std::endl;
    FullingMap(_array, len, R);
    proxod(_array, len, R, lenVect / 4, lenVect / 4);

    std::cout << std::endl;
    /*for(int i = 0; i < _array.size(); i++)
    {
        for(int j = 0; j < _array[i].size(); j++)
        {
            std::cout << std::fixed << std::setprecision(2) << std::setw(6) << _array[i][j] << " ";
        }
        std::cout << std::endl;
    }*/

    //return 0;
    sf::RenderWindow window(sf::VideoMode(block_size*len, block_size*len), "Diamond Square");

    std::vector<std::vector<sf::RectangleShape> > shapes;
    std::vector<sf::RectangleShape> shapes2;
    for(int x = lenVect/4, i = 0; x < len + lenVect / 4; x++, i++)
    {
        std::vector<sf::RectangleShape> _arr1;
        for(int y = lenVect/4, j = 0; y < len + lenVect / 4; y++, j++)
        {
            int result = ((int)_array[x][y])%255;
            if(result >= 256)
                result = 255;
            if(result < 0)
                result = -result;
           // std::cout << std::fixed << std::setprecision(2) << std::setw(6) << result << " ";
            sf::RectangleShape rs(sf::Vector2f(block_size, block_size));
            //rs.setFillColor(sf::Color(result, result, result));
            rs.setFillColor(SelectColor(result));
            rs.setPosition(i*block_size, j*block_size);
            _arr1.push_back(rs);
        }
        shapes.push_back(_arr1);
       // std::cout << std::endl;
    }

    for(auto &p : sh2)
    {
        sf::RectangleShape rs(sf::Vector2f(block_size, block_size));
        rs.setFillColor(sf::Color(255, 0, 0));
        rs.setPosition((p.first-(len - 1)/2)*block_size, (p.second-(len-1)/2)*block_size);
        shapes2.push_back(rs);
    }

    int X = 0,
        Y = 0;
    int slen = len-1;
    int Count = true;
    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code)
                    {
                        case sf::Keyboard::Left:

                            if (X - lenVect / 4 <= 0)
                            {
                                for (int i = 0; i < lenVect / 2; i++)
                                    _array.insert(_array.begin(),std::vector<double>(lenVect, 0));

                                _array[X + lenVect - 1][0] = RandM.Random(RMIN, RMAX);
                                _array[X + lenVect - 1][Y + lenVect - 1] = RandM.Random(RMIN, RMAX);

                                _array[X + lenVect + lenVect / 4 - 1][Y + lenVect / 4] = RandM.Random(RMIN, RMAX);
                                _array[X + lenVect + lenVect / 4 - 1][Y + lenVect / 4 + lenVect / 2] = RandM.Random(RMIN, RMAX);

                                _array[0][Y + lenVect / 2] = RandM.Random(RMIN, RMAX);

                                proxod(_array, len, R, lenVect/4, Y + lenVect / 4);
                                Scale(_array, len, len + lenVect/4 - 1, lenVect/4);
                                /*if (X == 0)
                                    X += lenVect / 4;*/
                                X = lenVect / 2;
                            }
                            else X -= lenVect / 4;

                            for (int x = X, i = 0; i < len; x++, i++)
                            {
                                for (int y = Y + lenVect / 4, j = 0; j < len; y++, j++)
                                {
                                    int result = ((int) _array[x][y]) % 255;
                                    if (result >= 256)
                                        result = 255;
                                    if (result < 0)
                                        result = -result;
                                    sf::RectangleShape rs(sf::Vector2f(block_size, block_size));
                                    rs.setFillColor(SelectColor(result));
                                    rs.setPosition(i * block_size, j * block_size);
                                    shapes[i][j] = rs;
                                }
                            }
                            break;

                        case sf::Keyboard::Right:
                            if (X + len + lenVect / 4 >= _array.size() - lenVect / 4)
                            {
                                for (int i = 0; i < lenVect / 2; i++)
                                    _array.push_back(std::vector<double>(lenVect, 0));

                                int max = 150;
                                _array[X + lenVect - 1][0] = RandM.Random(0, max);
                                _array[X + lenVect - 1][Y + lenVect - 1] = RandM.Random(0, max);

                                int size = _array.size();

                                _array[X + lenVect + lenVect / 4 - 1][Y + lenVect / 4] = RandM.Random(0, max);
                                _array[X + lenVect + lenVect / 4 - 1][Y + lenVect / 4 + lenVect / 2] = RandM.Random(0,
                                                                                                                    max);

                                _array[size - 1][Y + lenVect / 2] = RandM.Random(0, max);

                                proxod(_array, len, R, X + len - 1 + lenVect / 4, Y + lenVect / 4);
                                Scale(_array, len, X + len - 1 + lenVect / 4, lenVect/4);
                                if (X == 0)
                                    X += lenVect / 4;
                            }
                            X += lenVect / 4;
                            for (int x = X, i = 0; i < len; x++, i++)
                            {
                                for (int y = Y + lenVect / 4, j = 0; j < len; y++, j++)
                                {
                                    int result = ((int) _array[x][y]) % 255;
                                    if (result >= 256)
                                        result = 255;
                                    if (result < 0)
                                        result = -result;
                                    sf::RectangleShape rs(sf::Vector2f(block_size, block_size));
                                    //rs.setFillColor(sf::Color(result, result, result));
                                    rs.setFillColor(SelectColor(result));
                                    rs.setPosition(i * block_size, j * block_size);
                                    shapes[i][j] = rs;
                                }
                            }
                            break;
                        case sf::Keyboard::Space:
                            Scale(_array, len, X + lenVect/4, lenVect/4);
                            for (int x = X, i = 0; i < len; x++, i++)
                            {
                                for (int y = Y + lenVect / 4, j = 0; j < len; y++, j++)
                                {
                                    int result = ((int) _array[x][y]) % 255;
                                    if (result >= 256)
                                        result = 255;
                                    if (result < 0)
                                        result = -result;
                                    sf::RectangleShape rs(sf::Vector2f(block_size, block_size));
                                    //rs.setFillColor(sf::Color(result, result, result));
                                    rs.setFillColor(SelectColor(result));
                                    rs.setPosition(i * block_size, j * block_size);
                                    shapes[i][j] = rs;
                                }
                            }
                            for(auto &p : sh2)
                            {
                                sf::RectangleShape rs(sf::Vector2f(block_size, block_size));
                                rs.setFillColor(sf::Color(255, 0, 0));
                                rs.setPosition((p.first-X)*block_size, (p.second - len/2)*block_size);
                                std::cout << p.first - X << " " << p.second - len/2 << std::endl;
                                shapes2.push_back(rs);
                            }
                            break;
                        case sf::Keyboard::Home:
                            std::cout << std::endl;
                            for (int i = 0; i < _array.size(); i++)
                            {
                                for (int j = 0; j < _array[i].size(); j++)
                                {
                                    if ((i != X + len - 2 + lenVect / 4) || (j != Y + lenVect / 4))
                                        std::cout << std::fixed << std::setprecision(2) << std::setw(6)
                                                  << (int) _array[i][j] << " ";
                                    else std::cout << std::fixed << std::setprecision(2) << std::setw(6) << -1 << " ";
                                }
                                std::cout << std::endl;
                            }
                            break;
                    }
                    break;
            }
        }

        window.clear();
        for(auto &p : shapes)
        {
            for(auto &p1 : p)
            {
                window.draw(p1);
            }
        }
        for(auto &p : shapes2)
        {
            window.draw(p);
        }
        window.display();
    }

    return 0;
}
