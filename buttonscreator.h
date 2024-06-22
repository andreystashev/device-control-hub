#ifndef BUTTONSCREATOR_H
#define BUTTONSCREATOR_H
#include "ui_guicreator.h"
#include "networkcreator.h"


class buttonsCreator: public QObject
{
    Q_OBJECT
public:
    explicit buttonsCreator() {};
    ~buttonsCreator() = default;
    void chartScope(QLabel *cells[], QLabel *cellsInfo[], QLabel *place, const QString nameMassive[], int elementsCount, int x, int y, int width);
    void photoButton(unsigned int time, networkCreator* sock);
    void returnButton(unsigned int time, networkCreator* sock);
    void landingButton(unsigned int time, networkCreator* sock);
    void detonateButton(unsigned int time, networkCreator* sock);
    void targetButtons(QRadioButton* button[],Ui::guiUI* ui);

private:
    struct commandMessage
    {
        uint32_t id;
        uint16_t timeReturn;
        uint8_t timeCommand;
        uint8_t commandCode;
        uint8_t commandParam;
    };

    QByteArray commandContainer;
    commandMessage messageObject;
};


#endif // BUTTONSCREATOR_H
