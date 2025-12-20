#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <QMainWindow>
#include <QFrame>
#include <QPushButton>
#include <QListWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class SplashScreen : public QWidget {
    Q_OBJECT

private:
    QLabel* titleLabel;
    QProgressBar* progressBar;
    QTimer* progressTimer;
    int currentProgress;

public:
    SplashScreen(QWidget* parent = nullptr) : QWidget(parent), currentProgress(0) {
        setFixedSize(500, 300);
        setWindowTitle("1Up Engine");
        setStyleSheet("background-color: #1e1e1e;");

        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignCenter);
        layout->setSpacing(30);

        titleLabel = new QLabel("Loading 1UpEngine...", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("color: #ffffff; font-size: 24px; font-weight: bold;");

        progressBar = new QProgressBar(this);
        progressBar->setRange(0, 100);
        progressBar->setValue(0);
        progressBar->setFixedHeight(10);
        progressBar->setStyleSheet(
            "QProgressBar {"
            "    border: none;"
            "    border-radius: 5px;"
            "    background-color: #333333;"
            "}"
            "QProgressBar::chunk {"
            "    border-radius: 5px;"
            "    background-color: #0078d4;"
            "}"
        );

        layout->addWidget(titleLabel);
        layout->addWidget(progressBar);

        progressTimer = new QTimer(this);
        connect(progressTimer, &QTimer::timeout, this, &SplashScreen::updateProgress);
        progressTimer->start(50);
    }

private slots:
    void updateProgress() {
        currentProgress += 2;
        progressBar->setValue(currentProgress);

        if (currentProgress >= 100) {
            progressTimer->stop();
            QTimer::singleShot(500, this, [this]() {
                emit loadingComplete();
                close();
            });
        }
    }

signals:
    void loadingComplete();

private:
    void openMainWindow() {
        emit loadingComplete();
    }
};

class MenuSystem : public QMainWindow {
    Q_OBJECT

private:
    QWidget* centralWidget;
    QHBoxLayout* mainLayout;
    QFrame* sidebar;
    QWidget* contentArea;
    QLabel* contentLabel;
    QLabel* titleLabel;
    QPushButton* toggleButton;
    QPushButton* themeButton;
    QListWidget* menuList;
    bool sidebarVisible;
    bool darkTheme;

public:
    MenuSystem(QWidget* parent = nullptr) : QMainWindow(parent), sidebarVisible(true), darkTheme(true) {
        setWindowTitle("1 Up Engine");
        setMinimumSize(900, 600);
        resize(1200, 800);
        show();
        raise();

        centralWidget = new QWidget(this);
        mainLayout = new QHBoxLayout(centralWidget);
        mainLayout->setContentsMargins(0, 0, 0, 0);
        mainLayout->setSpacing(0);

        createSidebar();
        createContent();

        setCentralWidget(centralWidget);
        applyTheme();
    }

private:
    void createSidebar() {
        sidebar = new QFrame(centralWidget);
        sidebar->setObjectName("sidebar");
        sidebar->setFixedWidth(280);

        QVBoxLayout* sidebarLayout = new QVBoxLayout(sidebar);
        sidebarLayout->setContentsMargins(0, 0, 0, 0);
        sidebarLayout->setSpacing(0);

        QWidget* headerWidget = new QWidget(sidebar);
        QHBoxLayout* headerLayout = new QHBoxLayout(headerWidget);
        headerLayout->setContentsMargins(15, 15, 15, 15);

        toggleButton = new QPushButton("☰", headerWidget);
        toggleButton->setObjectName("toggleBtn");
        toggleButton->setCursor(Qt::PointingHandCursor);
        toggleButton->setFixedSize(40, 40);
        toggleButton->setToolTip("Toggle Sidebar");
        connect(toggleButton, &QPushButton::clicked, this, &MenuSystem::toggleSidebar);

        themeButton = new QPushButton("☀️", headerWidget);
        themeButton->setObjectName("themeBtn");
        themeButton->setCursor(Qt::PointingHandCursor);
        themeButton->setFixedSize(40, 40);
        themeButton->setToolTip("Toggle Theme");
        connect(themeButton, &QPushButton::clicked, this, &MenuSystem::toggleTheme);

        headerLayout->addWidget(toggleButton);
        headerLayout->addStretch();
        headerLayout->addWidget(themeButton);

        sidebarLayout->addWidget(headerWidget);

        QLabel* sidebarTitle = new QLabel("PROJECTS", sidebar);
        sidebarTitle->setObjectName("sidebarTitle");
        sidebarTitle->setAlignment(Qt::AlignCenter);
        sidebarLayout->addWidget(sidebarTitle);

        menuList = new QListWidget(sidebar);
        menuList->addItem("🏠 Home");
        menuList->addItem("📁 Open Project");
        menuList->addItem("➕ New Project");
        menuList->addItem("⚙️ Settings");
        menuList->addItem("❓ Help");
        menuList->addItem("ℹ️ About");

        connect(menuList, &QListWidget::itemClicked, this, &MenuSystem::onMenuItemClicked);

        sidebarLayout->addWidget(menuList);

        mainLayout->addWidget(sidebar);
    }

    void createContent() {
        contentArea = new QWidget(centralWidget);
        contentArea->setObjectName("contentArea");
        QVBoxLayout* contentLayout = new QVBoxLayout(contentArea);
        contentLayout->setContentsMargins(40, 40, 40, 40);
        contentLayout->setSpacing(20);
        QWidget* topBar = new QWidget(contentArea);
        topBar->setObjectName("topBar");
        QHBoxLayout* topBarLayout = new QHBoxLayout(topBar);
        topBarLayout->setContentsMargins(0, 0, 0, 20);
        QPushButton* contentToggleBtn = new QPushButton("☰", topBar);
        contentToggleBtn->setObjectName("contentToggleBtn");
        contentToggleBtn->setCursor(Qt::PointingHandCursor);
        contentToggleBtn->setFixedSize(40, 40);
        contentToggleBtn->setToolTip("Show Sidebar");
        contentToggleBtn->setVisible(!sidebarVisible);
        connect(contentToggleBtn, &QPushButton::clicked, this, &MenuSystem::toggleSidebar);
        topBarLayout->addWidget(contentToggleBtn);
        topBarLayout->addStretch();
        contentLayout->addWidget(topBar);
        contentArea->setProperty("toggleButton", QVariant::fromValue((void*)contentToggleBtn));
        titleLabel = new QLabel("Welcome", contentArea);
        titleLabel->setObjectName("title");
        contentLayout->addWidget(titleLabel);
        contentLayout->addSpacing(30);
        contentLabel = new QLabel("No project was found", contentArea);
        contentLabel->setObjectName("content");
        contentLabel->setWordWrap(true);
        contentLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft);
        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(contentLabel);
        contentLabel->setGraphicsEffect(effect);
        contentLayout->addWidget(contentLabel, 1);
        mainLayout->addWidget(contentArea, 1);
    }

    void applyTheme() {
        QString theme;

        if (darkTheme) {
            themeButton->setText("☀️");
            theme =
            "QMainWindow { background-color: #1e1e1e; }"
            "QFrame#sidebar { "
            "    background-color: #252526; "
            "    border-right: 1px solid #3e3e42; "
            "}"
            "QWidget#contentArea { background-color: #1e1e1e; }"
            "QListWidget { "
            "    background-color: #252526; "
            "    color: #cccccc; "
            "    border: none; "
            "    padding: 10px; "
            "    font-size: 15px; "
            "    outline: none; "
            "}"
            "QListWidget::item { "
            "    padding: 14px; "
            "    margin: 5px 10px; "
            "    border-radius: 8px; "
            "    border: none; "
            "}"
            "QListWidget::item:hover { "
            "    background-color: #2a2d2e; "
            "}"
            "QListWidget::item:selected { "
            "    background-color: #094771; "
            "    color: #ffffff; "
            "}"
            "QPushButton#toggleBtn, QPushButton#themeBtn { "
            "    background-color: #3e3e42; "
            "    color: white; "
            "    border: none; "
            "    border-radius: 8px; "
            "    font-size: 20px; "
            "}"
            "QPushButton#toggleBtn:hover, QPushButton#themeBtn:hover { "
            "    background-color: #505050; "
            "}"
            "QPushButton#contentToggleBtn { "
            "    background-color: #3e3e42; "
            "    color: white; "
            "    border: none; "
            "    border-radius: 8px; "
            "    font-size: 20px; "
            "}"
            "QPushButton#contentToggleBtn:hover { "
            "    background-color: #505050; "
            "}"
            "QLabel#title { "
            "    font-size: 32px; "
            "    font-weight: bold; "
            "    color: #ffffff; "
            "}"
            "QLabel#content { "
            "    font-size: 18px; "
            "    color: #9d9d9d; "
            "}"
            "QLabel#sidebarTitle { "
            "    font-size: 16px; "
            "    font-weight: bold; "
            "    color: #cccccc; "
            "    padding: 15px; "
            "    letter-spacing: 2px; "
            "}";
        } else {
            themeButton->setText("🌙");
            theme =
            "QMainWindow { background-color: #ffffff; }"
            "QFrame#sidebar { "
            "    background-color: #f3f3f3; "
            "    border-right: 1px solid #e0e0e0; "
            "}"
            "QWidget#contentArea { background-color: #ffffff; }"
            "QListWidget { "
            "    background-color: #f3f3f3; "
            "    color: #333333; "
            "    border: none; "
            "    padding: 10px; "
            "    font-size: 15px; "
            "    outline: none; "
            "}"
            "QListWidget::item { "
            "    padding: 14px; "
            "    margin: 5px 10px; "
            "    border-radius: 8px; "
            "    border: none; "
            "}"
            "QListWidget::item:hover { "
            "    background-color: #e8e8e8; "
            "}"
            "QListWidget::item:selected { "
            "    background-color: #0078d4; "
            "    color: #ffffff; "
            "}"
            "QPushButton#toggleBtn, QPushButton#themeBtn { "
            "    background-color: #e0e0e0; "
            "    color: #333333; "
            "    border: none; "
            "    border-radius: 8px; "
            "    font-size: 20px; "
            "}"
            "QPushButton#toggleBtn:hover, QPushButton#themeBtn:hover { "
            "    background-color: #d0d0d0; "
            "}"
            "QPushButton#contentToggleBtn { "
            "    background-color: #e0e0e0; "
            "    color: #333333; "
            "    border: none; "
            "    border-radius: 8px; "
            "    font-size: 20px; "
            "}"
            "QPushButton#contentToggleBtn:hover { "
            "    background-color: #d0d0d0; "
            "}"
            "QLabel#title { "
            "    font-size: 32px; "
            "    font-weight: bold; "
            "    color: #1e1e1e; "
            "}"
            "QLabel#content { "
            "    font-size: 18px; "
            "    color: #666666; "
            "}"
            "QLabel#sidebarTitle { "
            "    font-size: 16px; "
            "    font-weight: bold; "
            "    color: #333333; "
            "    padding: 15px; "
            "    letter-spacing: 2px; "
            "}";
        }

        setStyleSheet(theme);
        fadeContentLabel(contentLabel->text());
    }

    void fadeContentLabel(const QString& newText) {
        QGraphicsOpacityEffect* effect = qobject_cast<QGraphicsOpacityEffect*>(contentLabel->graphicsEffect());
        if (!effect) {
            effect = new QGraphicsOpacityEffect(contentLabel);
            contentLabel->setGraphicsEffect(effect);
        }

        QPropertyAnimation* fadeOut = new QPropertyAnimation(effect, "opacity");
        fadeOut->setDuration(200);
        fadeOut->setStartValue(1.0);
        fadeOut->setEndValue(0.0);
        fadeOut->setEasingCurve(QEasingCurve::InOutQuad);

        QPropertyAnimation* fadeIn = new QPropertyAnimation(effect, "opacity");
        fadeIn->setDuration(200);
        fadeIn->setStartValue(0.0);
        fadeIn->setEndValue(1.0);
        fadeIn->setEasingCurve(QEasingCurve::InOutQuad);

        connect(fadeOut, &QPropertyAnimation::finished, [this, newText, fadeIn]() {
            contentLabel->setText(newText);
            fadeIn->start(QAbstractAnimation::DeleteWhenStopped);
        });

        fadeOut->start(QAbstractAnimation::DeleteWhenStopped);
    }

private slots:
    void toggleSidebar() {
        QPushButton* contentToggleBtn = static_cast<QPushButton*>(
            contentArea->property("toggleButton").value<void*>()
        );
        QPropertyAnimation* widthAnim = new QPropertyAnimation(sidebar, "maximumWidth");
        widthAnim->setDuration(350);
        widthAnim->setEasingCurve(QEasingCurve::InOutCubic);
        QGraphicsOpacityEffect* sidebarEffect = new QGraphicsOpacityEffect(sidebar);
        sidebar->setGraphicsEffect(sidebarEffect);
        QPropertyAnimation* sidebarOpacity = new QPropertyAnimation(sidebarEffect, "opacity");
        sidebarOpacity->setDuration(350);
        sidebarOpacity->setEasingCurve(QEasingCurve::InOutQuad);
        QGraphicsOpacityEffect* btnEffect = qobject_cast<QGraphicsOpacityEffect*>(
            contentToggleBtn->graphicsEffect()
        );
        if (!btnEffect) {
            btnEffect = new QGraphicsOpacityEffect(contentToggleBtn);
            contentToggleBtn->setGraphicsEffect(btnEffect);
        }
        QPropertyAnimation* btnOpacity = new QPropertyAnimation(btnEffect, "opacity");
        btnOpacity->setDuration(250);
        btnOpacity->setEasingCurve(QEasingCurve::InOutQuad);

        if (sidebarVisible) {
            widthAnim->setStartValue(280);
            widthAnim->setEndValue(0);
            sidebarOpacity->setStartValue(1.0);
            sidebarOpacity->setEndValue(0.0);
            contentToggleBtn->setVisible(true);
            btnOpacity->setStartValue(0.0);
            btnOpacity->setEndValue(1.0);

            sidebarVisible = false;
        } else {
            widthAnim->setStartValue(0);
            widthAnim->setEndValue(280);
            sidebarOpacity->setStartValue(0.0);
            sidebarOpacity->setEndValue(1.0);
            sidebar->setMinimumWidth(280);
            btnOpacity->setStartValue(1.0);
            btnOpacity->setEndValue(0.0);
            connect(btnOpacity, &QPropertyAnimation::finished, [contentToggleBtn]() {
                contentToggleBtn->setVisible(false);
            });

            sidebarVisible = true;
        }

        connect(widthAnim, &QPropertyAnimation::finished, [this]() {
            if (!sidebarVisible) {
                sidebar->setMinimumWidth(0);
            }
        });

        widthAnim->start(QAbstractAnimation::DeleteWhenStopped);
        sidebarOpacity->start(QAbstractAnimation::DeleteWhenStopped);
        btnOpacity->start(QAbstractAnimation::DeleteWhenStopped);
    }

    void toggleTheme() {
        darkTheme = !darkTheme;
        applyTheme();
    }

    void onMenuItemClicked(QListWidgetItem* item) {
        QString itemText = item->text();
        QString newText;

        if (itemText.contains("Home")) {
            newText = "No project was found";
        } else if (itemText.contains("Open Project")) {
            newText = "Open an existing project from your computer";
        } else if (itemText.contains("New Project")) {
            newText = "Create a new project to get started";
        } else if (itemText.contains("Settings")) {
            newText = "Configure your preferences and settings";
        } else if (itemText.contains("Help")) {
            newText = "Get help and documentation";
        } else if (itemText.contains("About")) {
            newText = "1 Up Engine v0.1\nBuilt with Qt C++";
        } else {
            newText = "You selected: " + itemText;
        }

        fadeContentLabel(newText);
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    SplashScreen splash;
    splash.show();

    MenuSystem window;
    window.hide();

    QTimer::singleShot(3000, [&]() {
        splash.close();
        window.show();
        window.raise();
    });

    return app.exec();
}

#include "main.moc"