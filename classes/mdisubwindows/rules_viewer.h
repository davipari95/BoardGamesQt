#ifndef RULES_VIEWER_H
#define RULES_VIEWER_H

#include <QMdiSubWindow>
#include <QWidget>

namespace Ui {
class RulesViewer;
}

/**
 * @brief Window for showing the game rules
 */
class RulesViewer : public QMdiSubWindow
{
        Q_OBJECT

    public:
        //Constructor
        /**
         * @brief Initialize this class showing the rules of the game given in `gameName`.
         * @param[in] gameName A string with the game name.
         * @param[in] parent Object parent where this class is initialized.
         */
        explicit RulesViewer(const QString gameName, QWidget *parent = nullptr);

        //Destructor
        ~RulesViewer();

    private:
        //Variables
        /**
         * @brief User interface.
         */
        Ui::RulesViewer *ui;

        //Functions
        /**
         * @brief Initalize all UI components that cannot be initialized via designer.
         */
        void initializeComponents();
        /**
         * @brief Retrieve the HTML file that contains rules and show on text browser.
         * @param[in] gameName The game which you want to show rules.
         */
        void showRules(const QString gameName);
};

#endif // RULES_VIEWER_H
