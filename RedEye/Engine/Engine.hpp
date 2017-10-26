class Engine{
public:
    void Start();
    void Update();
    void End();
};

class Screen{
private:
    Screen();
    static Screen * m_pInstance;
    int ScreenWidth = 0;
    int ScreenHeight = 0;
public:
    static Screen * getInstance();

    void setWidthAndHeight(int width,int height);

    int getWidth();
    int getHeight();
};
