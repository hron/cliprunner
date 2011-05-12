#include "cliprunner.h"

#include <KDebug>
#include <KIcon>
#include <KAction>
#include <KShortcut>
#include <QtGui/QClipboard>
#include <QtDBus/QtDBus>


cliprunner::cliprunner(QObject *parent, const QVariantList& args)
    : Plasma::AbstractRunner(parent, args)
{
    Q_UNUSED(args);
    setObjectName(QLatin1String("Browse Clipboard"));
    m_icon = KIcon(QLatin1String("klipper"));

    addSyntax(Plasma::RunnerSyntax(QLatin1String(":q:"),
                                   i18n("Show Clipboard")));
    KAction *action = new KAction(this);
    action->setObjectName("test");

    action->setGlobalShortcut(KShortcut(Qt::ALT + Qt::Key_NumberSign));
    this->connect(action, SIGNAL(triggered()), SLOT(hotkeyTrigger()));
    this->addAction(QString("test"), action);
    klipper = new QDBusInterface("org.kde.klipper",
                                 "/klipper", "org.kde.klipper.klipper");
    krunner = new QDBusInterface("org.kde.krunner", "/App",
                                 "org.kde.krunner.App");
}

cliprunner::~cliprunner()
{
}

void cliprunner::hotkeyTrigger() {
    krunner->call("querySingleRunner", "cliprunner", "_inttrigger");
}

void cliprunner::match(Plasma::RunnerContext &context)
{
    QString term = context.query();

    if (term.length() < 3)
        return;

    if (!context.isValid())
        return;

    if (!klipper->isValid()) {
        return;
    }


    QDBusReply<QStringList> clipList =
        klipper->call("getClipboardHistoryMenu");
    if (clipList.isValid()) {
        foreach(const QString &clipString, (QStringList) clipList) {
            Plasma::QueryMatch match(this);
            if (term != "_inttrigger") {
                if (clipString == term) {
                    match.setRelevance(1);
                    match.setType(Plasma::QueryMatch::ExactMatch);
                } else if (clipString.contains(term, Qt::CaseInsensitive)
                          ) {
                    match.setType(Plasma::QueryMatch::PossibleMatch);
                    match.setRelevance(0.5);
                } else {
                    continue;
                }

            } else {
                term.clear();
            }

            match.setIcon(m_icon);
            match.setData(clipString);
            match.setText(QString());
            match.setSubtext(clipString);


            context.addMatch(term, match);
        }
    }
}

void cliprunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)
}

#include "cliprunner.moc"
