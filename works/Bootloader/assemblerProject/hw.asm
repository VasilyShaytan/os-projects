[BITS 16]
[ORG 0x7C00]

	mov si, HelloString	; Записываем в стек указатель на строку
	call PrintString	; Вызов процедуры печати строки
	jmp $				; Бесконечный цикл

PrintCharacter:		; Процедура печати символа
	mov ah, 0x0E		; Флаг того, что нам нужно вывести на экран один символ
	mov bh, 0x00		; Номер страницы
	mov bl, 0x07		; Флаг того, что выводится светлый текст на черном фоне

	int 0x10			; Вызов прерывания видео
	ret					; Возращение к вызванной процедуре

PrintString:	; Процедура печати строки

next_character:
	mov al, [si]	; Берем один байт из строки и записываем его в регистр AL
	inc si		; Увеличиваем указатель SI
	or al, al	; Проверка конца строки
	jz exit_function
	call PrintCharacter ; Печатаем символ
	jmp next_character
	exit_function:
	ret

;Data
HelloString db 'Try bootloader | Hello World', 0

times 510 - ($ - $$) db 0	;Заполняем оставшиеся байты нулями
dw 0xAA55			;Добавляем сигнатуру в конец загрузчика
