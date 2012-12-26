;; -*-emacs-lisp-*-
;;
;; Emacs startup file, e.g.  /etc/emacs/site-start.d/50plasma-runner-cliprunner.el
;; for the Debian plasma-runner-cliprunner package
;;
;; Originally contributed by Nils Naumann <naumann@unileoben.ac.at>
;; Modified by Dirk Eddelbuettel <edd@debian.org>
;; Adapted for dh-make by Jim Van Zandt <jrv@debian.org>

;; The plasma-runner-cliprunner package follows the Debian/GNU Linux 'emacsen' policy and
;; byte-compiles its elisp files for each 'emacs flavor' (emacs19,
;; xemacs19, emacs20, xemacs20...).  The compiled code is then
;; installed in a subdirectory of the respective site-lisp directory.
;; We have to add this to the load-path:
(let ((package-dir (concat "/usr/share/"
                           (symbol-name debian-emacs-flavor)
                           "/site-lisp/plasma-runner-cliprunner")))
;; If package-dir does not exist, the plasma-runner-cliprunner package must have
;; removed but not purged, and we should skip the setup.
  (when (file-directory-p package-dir)
    (if (fboundp 'debian-pkg-add-load-path-item)
        (debian-pkg-add-load-path-item package-dir)
      (setq load-path (cons package-dir load-path)))
    (autoload 'plasma-runner-cliprunner-mode "plasma-runner-cliprunner-mode"
      "Major mode for editing plasma-runner-cliprunner files." t)
    (add-to-list 'auto-mode-alist '("\\.plasma-runner-cliprunner$" . plasma-runner-cliprunner-mode))))

