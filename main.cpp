#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <SFML/Graphics.hpp>

const unsigned int SET_WIDTH = 400;
const unsigned int SET_HEIGHT = 400;
const double DSET_WIDTH = 400.0;
const double DSET_HEIGHT = 400.0;

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

RandomM RandM(128);

double sumSr(std::vector<std::vector<double>> &_array, int x, int y, int len)
{
    double s1, s2, s3, s4;
    s1 = _array[x][y + len];
    s2 = _array[x][y - len];
    s3 = _array[x + len][y];
    s4 = _array[x - len][y];
    return (s1 + s2 + s3 + s4) / 4.0;
}

void proxod(std::vector<std::vector<double>> &_array, int len, double R)
{
    int lenArray = _array.size();
    for(int slen = len -1; slen >= 2; slen /=2)
    {
        for(int x = lenArray/4; x < len - 1 + lenArray/4; x += slen)
            for(int y = lenArray/4; y < len - 1 + lenArray /4; y += slen)
            {
                double sr = (_array[x][y] + _array[x + slen][y] + _array[x][y + slen] +
                        _array[x + slen][y + slen]) / 4 + RandM.Random(-R*slen, R*slen);
                _array[x+slen/2][y+slen/2] = sr;

                _array[x][y + slen / 2] = sumSr(_array, x, y + slen / 2, slen / 2) + RandM.Random(-R*slen, R*slen);
                _array[x + slen / 2][y] = sumSr(_array, x + slen / 2, y, slen / 2) + RandM.Random(-R*slen, R*slen);
                _array[x + slen / 2][y + slen] = sumSr(_array, x + slen / 2, y + slen, slen / 2) + RandM.Random(-R*slen, R*slen);
                _array[x + slen][y + slen / 2] = sumSr(_array, x + slen, y + slen / 2, slen / 2) + RandM.Random(-R*slen, R*slen);
            }

        //break;
    }
}

void FullingMap(std::vector<std::vector<double>> &_array, int len)
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
}

int main()
{
    int n = 8;
    int len = pow(2, n) + 1;
    int lenVect = pow(2, n + 1) + 1;
    double block_size = DSET_WIDTH / len;
    std::vector<std::vector<double>> _array(lenVect, std::vector<double>(lenVect, 0.0));
    std::cout << "установлена размерность: " << len << std::endl;
    FullingMap(_array, len);
    proxod(_array, len, 0.6);

    sf::RenderWindow window(sf::VideoMode(block_size*len, block_size*len), "Diamond Square");

    std::vector<std::vector<sf::RectangleShape> > shapes;
    for(int x = lenVect/4, i = 0; x < len + lenVect / 4; x++, i++)
    {
        std::vector<sf::RectangleShape> _arr1;
        for(int y = lenVect/4, j = 0; y < len + lenVect / 4; y++, j++)
        {
            int result = ((int)_array[x][y])%255;
            if(result >= 256)
                result = 255;
            if(result < 0)
                result = 0;
            std::cout << std::fixed << std::setprecision(2) << std::setw(6) << result << " ";
            sf::RectangleShape rs(sf::Vector2f(block_size, block_size));
            rs.setFillColor(sf::Color(result, result,result));
            rs.setPosition(j*block_size, i*block_size);
            _arr1.push_back(rs);
        }
        shapes.push_back(_arr1);
        std::cout << std::endl;
    }

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        for(auto &p : shapes)
        {
            for(auto &p1 : p)
            {
                window.draw(p1);
            }
        }
        window.display();
    }

    return 0;
}
