
#ifndef CLIPRUNNER_H
#define CLIPRUNNER_H

#include <plasma/abstractrunner.h>
#include <KIcon>

// Define our plasma Runner
class cliprunner : public Plasma::AbstractRunner {
    Q_OBJECT

public:
    // Basic Create/Destroy
    cliprunner( QObject *parent, const QVariantList& args );
    ~cliprunner();

    void match(Plasma::RunnerContext &context);
    void run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match);
};
// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_RUNNER(cliprunner, cliprunner)

#endif
