/*
 *   Copyright 2011, Jan Killius, jkillius@arcor.de
 *   Copyright (C) 2012 by Aleksei Gusev <aleksei.gusev@gmail.com>
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
#include "cliprunner.h"

#include <QtGui/QClipboard>
#include <QtDBus/QtDBus>

#include <KApplication>
#include <KIcon>
#include <KAction>
#include <KShortcut>
#include <KDebug>

cliprunner::cliprunner(QObject *parent, const QVariantList& args)
  : Plasma::AbstractRunner(parent, args) {
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

cliprunner::~cliprunner() {
}

void cliprunner::hotkeyTrigger() {
  krunner->call("querySingleRunner", "cliprunner", "_inttrigger");
}

void cliprunner::match(Plasma::RunnerContext &context) {
  QString term = context.query();

  if (term.length() < 3)
    return;

  if (!context.isValid())
    return;

  if (!klipper->isValid()) {
    return;
  }


  QDBusReply<QStringList> clipList = klipper->call("getClipboardHistoryMenu");

  if (clipList.isValid()) {
    foreach(const QString &clipString, (QStringList) clipList) {
      Plasma::QueryMatch match(this);
      if (term != "_inttrigger") {
	if (clipString == term) {
	  match.setRelevance(1);
	  match.setType(Plasma::QueryMatch::ExactMatch);
	} else if (clipString.contains(term, Qt::CaseInsensitive)) {
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
      match.setText(i18n("Copy %1", clipString));
      match.setId(clipString);

      context.addMatch(term, match);
    }
  }
}

void cliprunner::run(const Plasma::RunnerContext &context, const Plasma::QueryMatch &match)
{
  Q_UNUSED(context)
  //Copy words to clipboard
  kapp->clipboard()->setText(match.data().toString());
}

#include "cliprunner.moc"
