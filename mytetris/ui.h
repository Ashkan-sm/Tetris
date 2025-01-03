#ifndef UI_H
#define UI_H
#include <QVector2D>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <ctime>
#include <fstream>
using MyVariant = std::variant<int, QVector<QVector<int>> >;
class UI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int rows READ rows NOTIFY rowsChanged)
    Q_PROPERTY(int cols READ cols NOTIFY colsChanged)
    Q_PROPERTY(int score READ score WRITE setScore NOTIFY scoreChanged FINAL)
    Q_PROPERTY(int level READ level WRITE setLevel NOTIFY levelChanged FINAL)
    Q_PROPERTY(QVector<QVector<int>> next_obj_2 READ next_obj_2 WRITE setNext_obj_2 NOTIFY next_obj_2Changed FINAL)
    Q_PROPERTY(bool runnig READ runnig WRITE setRunnig NOTIFY runnigChanged FINAL)
    Q_PROPERTY(QString high_score READ high_score WRITE setHigh_score NOTIFY high_scoreChanged FINAL)

public:


    int timedelay=300;
    QTimer *timer = new QTimer(this);
    explicit UI(int rows, int cols, QObject *parent = nullptr);


    int rows() const { return m_rows; }
    int cols() const { return m_cols; }

    Q_INVOKABLE int get(int row, int col) const {
        if (row >= 0 && row < m_rows && col >= 0 && col < m_cols)
            return m_matrix[row][col];
        return -1;  // Return an invalid value if indices are out of bounds
    }

    Q_INVOKABLE void set(int row, int col, int value) {
        if (row >= 0 && row < m_rows && col >= 0 && col < m_cols) {
            m_matrix[row][col] = value;
            emit matrixChanged();
        }
    }
    QVector<QVector<int>> m_matrix;

    int score() const;

    void setScore(int newScore);

    QList<MyVariant> next_obj() const;

    void setNext_obj(const QList<MyVariant> &newNext_obj);

    QVector<QVector<int> > next_obj_2() const;
    void setNext_obj_2(const QVector<QVector<int> > &newNext_obj_2);

    int level() const;
    void setLevel(int newLevel);

    bool runnig() const;
    void setRunnig(bool newRunnig);

    QString high_score() const;
    void setHigh_score(const QString &newHigh_score);

public slots:

    QVector<QVector<int>> get_matrix();
    void rotate_right();
    void retry();
    void move_down(){
        updateCycle();
        updateCycle();
        updateCycle();
    };
    void updateCycle();


    void move_right(){
        int i=obj_list.length()-1;
        if(active_obj && check_colision_horizantal(std::get<int>(obj_list[i][0]),std::get<int>(obj_list[i][1]),std::get<QVector<QVector<int>>>(obj_list[i][2]),+1)){


        clear_obj(std::get<int>(obj_list[i][0]),std::get<int>(obj_list[i][1]),std::get<QVector<QVector<int>>>(obj_list[i][2]));

        obj_list[i][0]=std::get<int>(obj_list[i][0])+1;

        put_obj(std::get<int>(obj_list[i][0]),std::get<int>(obj_list[i][1]),std::get<QVector<QVector<int>>>(obj_list[i][2]));}

    }
    void move_left(){
        int i=obj_list.length()-1;
        if (active_obj && check_colision_horizantal(std::get<int>(obj_list[i][0]),std::get<int>(obj_list[i][1]),std::get<QVector<QVector<int>>>(obj_list[i][2]),-1)){

        clear_obj(std::get<int>(obj_list[i][0]),std::get<int>(obj_list[i][1]),std::get<QVector<QVector<int>>>(obj_list[i][2]));

        obj_list[i][0]=std::get<int>(obj_list[i][0])-1;

        put_obj(std::get<int>(obj_list[i][0]),std::get<int>(obj_list[i][1]),std::get<QVector<QVector<int>>>(obj_list[i][2]));}

    }


signals:
    void rowsChanged();
    void colsChanged();
    void matrixChanged();

    void scoreChanged();

    void next_objChanged();

    void next_obj_2Changed();

    void levelChanged();

    void runnigChanged();

    void high_scoreChanged();

private:
    void rotateMatrix(QVector<QVector<int>>& matrix);
    bool check_colision_vertical(int x,int y,QVector<QVector<int>>& obj);
    bool check_colision_horizantal(int x,int y,QVector<QVector<int>>& obj,int dir);
    bool check_colision_rotaion(int x,int y,QVector<QVector<int>>& obj);
    bool check_colision(int x,int y,QVector<QVector<int>>& obj);
    int m_rows{2};
    int m_cols;

    // 2D vector to represent the matrix

    const QVector<QVector<int>> shape_L={
        {0,0,0,0},
        {1,1,1,0},
        {0,0,1,0},
        {0,0,0,0}
    };
    const QVector<QVector<int>> shape_I={
        {0,0,0,0},
        {2,2,2,2},
        {0,0,0,0},
        {0,0,0,0}
    };
    QVector<QVector<int>> shape_Z={
        {0,0,0,0},
        {3,3,0,0},
        {0,3,3,0},
        {0,0,0,0}
    };
    QVector<QVector<int>> shape_P={
        {0,0,0,0},
        {4,4,4,0},
        {0,4,0,0},
        {0,0,0,0}
    };
    QVector<QVector<int>> shape_B={
        {0,0,0,0},
        {0,5,5,0},
        {0,5,5,0},
        {0,0,0,0}
    };
    QVector<QVector<int>> shape_S={
        {0,0,0,0},
        {0,6,6,0},
        {6,6,0,0},
        {0,0,0,0}
    };

    QVector<QVector<QVector<int>>> shapes={shape_I,shape_L,shape_P,shape_Z,shape_B,shape_S};

     // Create a QList<MyVariant> first

    QList<QList<MyVariant>> obj_list;

    int g_w=10,g_h=20;
    bool active_obj=false;


    void put_obj(int x,int y,QVector<QVector<int>> shape){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if (x+i<g_w && y+j<g_h){
                    if(shape[j][i]!=0){
                        m_matrix[y+j][x+i]=shape[j][i];
                    }
                }
            }
        }
        emit matrixChanged();

    }
    void clear_obj(int x,int y,QVector<QVector<int>> shape){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                if (x+i<g_w && y+j<g_h){
                    if(shape[j][i]!=0){
                        m_matrix[y+j][x+i]=0;

                    }
                }
            }
        }
        emit matrixChanged();

    }



    int m_score{0};

    QVector<QVector<int> > m_next_obj_2=shapes[2];
    int m_level{0};
    bool m_runnig{true};

    std::string line;

    QString m_high_score{};


};



#endif // UI_H
