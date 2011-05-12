#include "cliprunner.h"

#include <KDebug>
#include <KIcon>

cliprunner::cliprunner(QObject *parent, const QVariantList& args)
    : Plasma::AbstractRunner(parent, args)
{
    Q_UNUSED(args);
    setObjectName("cliprunner");
}

cliprunner::~cliprunner()
{
}


void cliprunner::match(Plasma::RunnerContext &context)
{

    const QString term = context.query();
    if (term.length() < 3) {
        return;
    }
    //TODO
}

void cliprunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
    Q_UNUSED(context)
}

#include "cliprunner.moc"
