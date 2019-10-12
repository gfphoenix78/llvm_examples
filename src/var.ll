; ModuleID = 'var.c'
source_filename = "var.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.14.0"

%struct.foo = type { i32, [16 x i8] }

@f1 = global %struct.foo { i32 12, [16 x i8] c"justing\00\00\00\00\00\00\00\00\00" }, align 4
@b = external global i32, align 4
@bp = external global i32*, align 8
@f2 = external global %struct.foo, align 4
@f3 = external global %struct.foo*, align 8
@a = common global i32 0, align 4
@ap = common global i32* null, align 8

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @func_b() #0 {
  %1 = load i32, i32* @b, align 4
  ret i32 %1
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32* @func_bp() #0 {
  %1 = load i32*, i32** @bp, align 8
  ret i32* %1
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @func_f2(%struct.foo* noalias sret) #0 {
  %2 = bitcast %struct.foo* %0 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 4 %2, i8* align 4 bitcast (%struct.foo* @f2 to i8*), i64 20, i1 false)
  ret void
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i1) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define %struct.foo* @func_f3() #0 {
  %1 = load %struct.foo*, %struct.foo** @f3, align 8
  ret %struct.foo* %1
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"Apple LLVM version 10.0.1 (clang-1001.0.46.4)"}
