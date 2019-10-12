; ModuleID = 'struct.c'
source_filename = "struct.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.14.0"

%struct.foo = type { i32, %struct.bar, %struct.foo* }
%struct.bar = type { i32, [32 x i8] }

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @setfoo(%struct.foo*, i32) #0 {
  %3 = alloca %struct.foo*, align 8
  %4 = alloca i32, align 4
  store %struct.foo* %0, %struct.foo** %3, align 8
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %4, align 4
  %6 = load %struct.foo*, %struct.foo** %3, align 8
  %7 = getelementptr inbounds %struct.foo, %struct.foo* %6, i32 0, i32 0
  %8 = load i32, i32* %7, align 8
  %9 = add nsw i32 %8, %5
  store i32 %9, i32* %7, align 8
  %10 = load i32, i32* %4, align 4
  %11 = load %struct.foo*, %struct.foo** %3, align 8
  %12 = getelementptr inbounds %struct.foo, %struct.foo* %11, i32 0, i32 1
  %13 = getelementptr inbounds %struct.bar, %struct.bar* %12, i32 0, i32 0
  store i32 %10, i32* %13, align 4
  %14 = load i32, i32* %4, align 4
  %15 = load %struct.foo*, %struct.foo** %3, align 8
  %16 = getelementptr inbounds %struct.foo, %struct.foo* %15, i32 0, i32 2
  %17 = load %struct.foo*, %struct.foo** %16, align 8
  %18 = getelementptr inbounds %struct.foo, %struct.foo* %17, i32 0, i32 0
  %19 = load i32, i32* %18, align 8
  %20 = add nsw i32 %19, %14
  store i32 %20, i32* %18, align 8
  %21 = load i32, i32* %4, align 4
  %22 = load %struct.foo*, %struct.foo** %3, align 8
  %23 = getelementptr inbounds %struct.foo, %struct.foo* %22, i32 0, i32 2
  %24 = load %struct.foo*, %struct.foo** %23, align 8
  %25 = getelementptr inbounds %struct.foo, %struct.foo* %24, i32 0, i32 1
  %26 = getelementptr inbounds %struct.bar, %struct.bar* %25, i32 0, i32 0
  store i32 %21, i32* %26, align 4
  %27 = load i32, i32* %4, align 4
  %28 = load %struct.foo*, %struct.foo** %3, align 8
  %29 = getelementptr inbounds %struct.foo, %struct.foo* %28, i32 0, i32 1
  %30 = getelementptr inbounds %struct.bar, %struct.bar* %29, i32 0, i32 0
  %31 = load i32, i32* %30, align 4
  %32 = add nsw i32 %27, %31
  %33 = load %struct.foo*, %struct.foo** %3, align 8
  %34 = getelementptr inbounds %struct.foo, %struct.foo* %33, i32 0, i32 0
  %35 = load i32, i32* %34, align 8
  %36 = add nsw i32 %35, %32
  store i32 %36, i32* %34, align 8
  %37 = load i32, i32* %4, align 4
  %38 = load %struct.foo*, %struct.foo** %3, align 8
  %39 = getelementptr inbounds %struct.foo, %struct.foo* %38, i32 0, i32 0
  %40 = load i32, i32* %39, align 8
  %41 = add nsw i32 %37, %40
  %42 = load %struct.foo*, %struct.foo** %3, align 8
  %43 = getelementptr inbounds %struct.foo, %struct.foo* %42, i32 0, i32 2
  %44 = load %struct.foo*, %struct.foo** %43, align 8
  %45 = getelementptr inbounds %struct.foo, %struct.foo* %44, i32 0, i32 0
  %46 = load i32, i32* %45, align 8
  %47 = add nsw i32 %46, %41
  store i32 %47, i32* %45, align 8
  ret void
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"Apple LLVM version 10.0.1 (clang-1001.0.46.4)"}
