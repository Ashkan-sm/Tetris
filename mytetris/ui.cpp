#include "ui.h"

UI::UI(int rows, int cols, QObject *parent) : QObject(parent), m_rows(rows), m_cols(cols)
{



    connect(timer, &QTimer::timeout, this, &UI::updateCycle);
    timer->start(timedelay);


    // Initialize the matrix (a 2D QVector) with default values (0)
    for (int i = 0; i < rows; ++i) {
        QVector<int> row(cols, 0);
        m_matrix.append(row);
    }
}

QVector<QVector<int> > UI::get_matrix()
{

    return m_matrix;
}

void UI::rotate_right()
{
    int i=obj_list.length()-1;
    if (active_obj && check_colision_rotaion(std::get<int>(obj_list[i][0]),std::get<int>(obj_list[i][1]),std::get<QVector<QVector<int>>>(obj_list[i][2]))){


    clear_obj(std::get<int>(obj_list[i][0]),std::get<int>(obj_list[i][1]),std::get<QVector<QVector<int>>>(obj_list[i][2]));
    rotateMatrix(std::get<QVector<QVector<int>>>(obj_list[obj_list.length()-1][2]));
    put_obj(std::get<int>(obj_list[i][0]),std::get<int>(obj_list[i][1]),std::get<QVector<QVector<int>>>(obj_list[i][2]));}
}

void UI::retry()
{
    std::ofstream outputFile("score.txt");
    outputFile << score();
    outputFile.close();
    setHigh_score(QString::number(score()));
    setLevel(0);
    timedelay=300;
    setScore(0);
    for (int i=0;i<20;i++){
        for (int j=0;j<10;j++){
            m_matrix[i][j]=0;
        }
    }
}

void UI::updateCycle()
{

    std::srand(std::time(0));

    if(!active_obj && runnig()){
        int n=rand();
        obj_list.push_back({3,-1,next_obj_2()});
        setNext_obj_2(shapes[n%shapes.length()]);

        if(check_colision(std::get<int>(obj_list[0][0]),std::get<int>(obj_list[0][1]),std::get<QVector<QVector<int>>>(obj_list[0][2]))){
            timedelay-=1;
            timer->setInterval(timedelay);
            active_obj=1;
            put_obj(std::get<int>(obj_list[0][0]),std::get<int>(obj_list[0][1]),std::get<QVector<QVector<int>>>(obj_list[0][2]));
        }
        else{
            std::ofstream outputFile("score.txt");
            outputFile << score();
            outputFile.close();
            setHigh_score(QString::number(score()));
            setRunnig(false);
        }

    }


    else{
        for (int i=0;i<obj_list.length();i++){
            if(check_colision_vertical(std::get<int>(obj_list[i][0]),std::get<int>(obj_list[i][1]),std::get<QVector<QVector<int>>>(obj_list[i][2]))){
                clear_obj(std::get<int>(obj_list[i][0]),std::get<int>(obj_list[i][1]),std::get<QVector<QVector<int>>>(obj_list[i][2]));

                obj_list[i][1]=std::get<int>(obj_list[i][1])+1;

                put_obj(std::get<int>(obj_list[i][0]),std::get<int>(obj_list[i][1]),std::get<QVector<QVector<int>>>(obj_list[i][2]));

            }
            else{
                active_obj=0;


                int a=0;
                for(int j=0;j<20;j++){
                    int t=0;
                    for(int i=0;i<10;i++){
                        if(m_matrix[j][i]!=0){
                            t++;
                        }
                    }
                    if(t==10){
                        a++;

                        for(int i=0;i<10;i++){

                            for(int jc=j;jc>0;jc--){
                                m_matrix[jc][i]=m_matrix[jc-1][i];
                            }
                        }
                    }

                }
                setScore(score()+(a*a));
                setLevel((300-timedelay)/10);
                obj_list.pop_back();
            }

        }
    }

    emit matrixChanged();

}


void UI::rotateMatrix(QVector<QVector<int>> &matrix)
{
    int n = matrix.size(); // Assuming the matrix is n x n

    // Perform the rotation by transposing and then reversing columns
    for (int i = 0; i < n / 2; ++i) {
        for (int j = i; j < n - i - 1; ++j) {
            // Rotate the four elements in the cycle
            int temp = matrix[i][j];
            matrix[i][j] = matrix[n - j - 1][i];
            matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
            matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
            matrix[j][n - i - 1] = temp;
        }
    }

}

bool UI::check_colision_vertical(int x,int y,QVector<QVector<int> > &obj)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if(obj[j][i]!=0)
            {

                if(y+j+1>=20)
                {

                    return false;

                }
                if(m_matrix[y+j+1][x+i]!=0){
                    if (j+1>=4){
                        return false;
                    }
                    else if(obj[j+1][i]==0){
                        return false;
                    }

                }

            }
        }
    }
    return true;
}

bool UI::check_colision_horizantal(int x, int y, QVector<QVector<int> > &obj,int dir)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if(obj[j][i]!=0)
            {

                if(x+i+dir>=10 || x+i+dir<0)
                {

                    return false;

                }
                if(m_matrix[y+j][x+i+dir]!=0){
                    if (i+dir>=4 || i+dir<0){
                        return false;
                    }
                    else if(obj[j][i+dir]==0){
                        return false;
                    }

                }

            }
        }
    }
    return true;
}

bool UI::check_colision_rotaion(int x, int y, QVector<QVector<int>> &obj)
{
    QVector<QVector<int>> obj_copy=obj;
    rotateMatrix(obj_copy);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if(obj_copy[j][i]!=0)
            {

                if(x+i>=10 || x+i<0 || y+j<0 || y+j>=20)
                {

                    return false;

                }
                if(obj[j][i]==0 && m_matrix[y+j][x+i]!=0){
                    return false;
                }


            }
        }
    }
    return true;
}

bool UI::check_colision(int x, int y, QVector<QVector<int> > &obj)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if(obj[j][i]!=0)
            {

                if( m_matrix[y+j][x+i]!=0){
                    return false;
                }

            }
        }
    }
    return true;
}

int UI::score() const
{
    return m_score;
}

void UI::setScore(int newScore)
{
    if (m_score == newScore)
        return;
    m_score = newScore;
    emit scoreChanged();
}






QVector<QVector<int> > UI::next_obj_2() const
{
    return m_next_obj_2;
}

void UI::setNext_obj_2(const QVector<QVector<int> > &newNext_obj_2)
{
    if (m_next_obj_2 == newNext_obj_2)
        return;
    m_next_obj_2 = newNext_obj_2;
    emit next_obj_2Changed();
}

int UI::level() const
{
    return m_level;
}

void UI::setLevel(int newLevel)
{
    if (m_level == newLevel)
        return;
    m_level = newLevel;
    emit levelChanged();
}

bool UI::runnig() const
{
    return m_runnig;
}

void UI::setRunnig(bool newRunnig)
{
    if (m_runnig == newRunnig)
        return;
    m_runnig = newRunnig;
    emit runnigChanged();
}

QString UI::high_score() const
{
    return m_high_score;
}

void UI::setHigh_score(const QString &newHigh_score)
{
    if (m_high_score == newHigh_score)
        return;
    m_high_score = newHigh_score;
    emit high_scoreChanged();
}
