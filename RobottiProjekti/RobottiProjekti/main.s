	.module main.c
	.area text(rom, con, rel)
	.dbfile ./main.c
	.area data(ram, con, rel)
	.dbfile ./main.c
_timeT::
	.blkb 2
	.area idata(rom,lit)
	.word 0
	.area data(ram, con, rel)
	.dbfile ./main.c
	.dbfile Z:\robotti\Robor7\ROBOTT~1\ROBOTT~1\main.c
	.dbsym e timeT _timeT I
_timeUltra::
	.blkb 2
	.area idata(rom,lit)
	.word 0
	.area data(ram, con, rel)
	.dbfile Z:\robotti\Robor7\ROBOTT~1\ROBOTT~1\main.c
	.dbsym e timeUltra _timeUltra I
_timeUltraRead::
	.blkb 2
	.area idata(rom,lit)
	.word 0
	.area data(ram, con, rel)
	.dbfile Z:\robotti\Robor7\ROBOTT~1\ROBOTT~1\main.c
	.dbsym e timeUltraRead _timeUltraRead I
_milliT::
	.blkb 4
	.area idata(rom,lit)
	.word 0,0
	.area data(ram, con, rel)
	.dbfile Z:\robotti\Robor7\ROBOTT~1\ROBOTT~1\main.c
	.dbsym e milliT _milliT l
_distanceCM::
	.blkb 2
	.area idata(rom,lit)
	.word 0
	.area data(ram, con, rel)
	.dbfile Z:\robotti\Robor7\ROBOTT~1\ROBOTT~1\main.c
	.dbsym e distanceCM _distanceCM I
	.area text(rom, con, rel)
	.dbfile Z:\robotti\Robor7\ROBOTT~1\ROBOTT~1\main.c
	.dbfunc e main _main fV
_main::
	.dbline 0 ; func end
	jmp .
	.dbend
	.dbfunc e PinInterrupt _PinInterrupt fV
_PinInterrupt::
	pop A
	.dbline 0 ; func end
	reti
	.dbend
	.dbfunc e TestLoop _TestLoop fV
_TestLoop::
	.dbline 0 ; func end
	ret
	.dbend
	.dbfunc e Delay _Delay fV
;          delay -> X-5
_Delay::
	pop X
	.dbline 0 ; func end
	ret
	.dbsym l delay -5 I
	.dbend
	.area bss(ram, con, rel)
	.dbfile Z:\robotti\Robor7\ROBOTT~1\ROBOTT~1\main.c
_buffer::
	.blkb 10
	.dbsym e buffer _buffer A[10:10]c
