#ifndef RULES_VIEWER_H
#define RULES_VIEWER_H

#include <QMdiSubWindow>
#include <QWidget>

namespace Ui {
class RulesViewer;
}

class RulesViewer : public QMdiSubWindow
{
        Q_OBJECT

    public:
        //Constructor
        explicit RulesViewer(const QString gameName, QWidget *parent = nullptr);

        //Destructor
        ~RulesViewer();

    private:
        //Variables
        Ui::RulesViewer *ui;

        //Functions
        void initializeComponents();
        void showRules(const QString gameName);
};

#endif // RULES_VIEWER_H
