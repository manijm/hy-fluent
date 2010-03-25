;;;
; Copyright (C) 2009  huys, huys03@gmail.com
;
; This program is free software: you can redistribute it and;or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program.  If not, see <http://www.gnu.org/licenses/>.

;; The function for reading the report file
(define (read-report-file filename)
  (let
    ((p (open-input-file (format #f "~a" filename))))
    (do
      ((x (read p) (read p)))
      (
        (or (number? x) (eof-object? x))
        (close-input-port p)
        (if (number? x) x #f)
      )
    )
  )
)

(define pfile (open-output-file "favg.dat"))

(do ((i  0 (+ i 5))(x 0.0)(y 0.0))
  ((> i 340))
  (begin
    (newline)
    (set! x (/ i 1000))
    (set! y (read-report-file (format #f "favg~03d.srp" i)))
    (display (format #f "~a     ~a" x  y) pfile)
    (newline pfile)
  )
)

(close-input-port pfile)

