/*
 *   Copyright 2011, Jan Killius, jkillius@arcor.de
 *
 *   Cliprunner is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Cliprunner is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CLIPRUNNER_H_
#define CLIPRUNNER_H_

#include <plasma/abstractrunner.h>
#include <KIcon>
#include <QtDBus/QtDBus>

// Define our plasma Runner
class cliprunner : public Plasma::AbstractRunner {
        Q_OBJECT

    public:
        // Basic Create/Destroy
        cliprunner(QObject *parent, const QVariantList& args);
        ~cliprunner();

        void match(Plasma::RunnerContext &context);
        void run(const Plasma::RunnerContext &context, 
		 const Plasma::QueryMatch &match);
    private:
        KIcon m_icon;
        QDBusInterface *klipper;
        QDBusInterface *krunner;

    public slots:
        void hotkeyTrigger();
};
// This is the command that links your applet to the .desktop file
K_EXPORT_PLASMA_RUNNER(cliprunner, cliprunner)

#endif  // CLIPRUNNER_H_
