#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QFile>
#include <QWebEngineView>
#include <QResource>
#include <QDialog>

class HtmlViewer : public QDialog {
    Q_OBJECT

public:
    HtmlViewer(const QString &htmlContent, QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("HTML Viewer");
        resize(1200, 800); // Set a larger default size for the window

        QVBoxLayout *layout = new QVBoxLayout(this);

        webView = new QWebEngineView(this);
        webView->setHtml(htmlContent);
        layout->addWidget(webView);

        setLayout(layout);
    }

private:
    QWebEngineView *webView;
};

class HtmlEditor : public QWidget {
    Q_OBJECT

public:
    HtmlEditor(QWidget *parent = nullptr) : QWidget(parent) {
        // Main layout
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Logo
        QLabel *logoLabel = new QLabel(this);
        QPixmap logo(":/images/logo.png");
        logoLabel->setPixmap(logo);
        logoLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(logoLabel);

        // Title label below the logo
        QLabel *titleLabel = new QLabel("Apex Html Viewer v1.0", this);
        titleLabel->setStyleSheet("color: gold; font-size: 20px; font-weight: bold;");
        titleLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(titleLabel);

        // Text editor
        textEdit = new QTextEdit(this);
        textEdit->setStyleSheet("background-color: black; color: teal;");
        layout->addWidget(textEdit);

        // View HTML button
        QPushButton *viewHtmlButton = new QPushButton("View Html", this);
        viewHtmlButton->setStyleSheet("background-color: gold; color: teal;");
        layout->addWidget(viewHtmlButton);

        // Color scheme selector
        QComboBox *colorSchemeCombo = new QComboBox(this);
        colorSchemeCombo->addItem("Default (Black Background, Teal Text)");
        colorSchemeCombo->addItem("Red Background, Gold Text");
        colorSchemeCombo->addItem("Dark Green Background, Black Text");
        colorSchemeCombo->addItem("Black Background, Teal Text");
        layout->addWidget(colorSchemeCombo);

        // Connect signals and slots
        connect(viewHtmlButton, &QPushButton::clicked, this, &HtmlEditor::viewHtml);
        connect(colorSchemeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &HtmlEditor::changeColorScheme);

        setLayout(layout);
    }

private slots:
    void viewHtml() {
        QString htmlContent = textEdit->toPlainText();
        HtmlViewer *viewer = new HtmlViewer(htmlContent, this);
        viewer->exec(); // Open the viewer as a modal dialog
    }

    void changeColorScheme(int index) {
        switch (index) {
            case 0: // Default
                textEdit->setStyleSheet("background-color: black; color: teal;");
                break;
            case 1: // Red Background, Gold Text
                textEdit->setStyleSheet("background-color: red; color: gold;");
                break;
            case 2: // Dark Green Background, Black Text
                textEdit->setStyleSheet("background-color: darkgreen; color: black;");
                break;
            case 3: // Black Background, Teal Text
                textEdit->setStyleSheet("background-color: black; color: teal;");
                break;
        }
    }

private:
    QTextEdit *textEdit;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Load the logo from the resource file
    QResource::registerResource("resources.rcc");

    // Set application style
    app.setStyleSheet("QWidget { background-color: teal; color: gold; }");

    HtmlEditor editor;
    editor.setWindowTitle("Apex Html Editor And Viewer v1.0");
    editor.resize(800, 600);
    editor.show();

    return app.exec();
}

#include "main.moc"
